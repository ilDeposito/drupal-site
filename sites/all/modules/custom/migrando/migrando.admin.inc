<?php

/**
 * @file
 */
define("MIGRANDO_API", "http://www.ildeposito.org/");
//define("MIGRANDO_API", "http://ildeposito.local/");
define("MIGRANDO_FILES", 'http://www.ildeposito.org/sites/default/files/');

function migrando_settings_form() {
  $form = array();

  $form['impostazioni_generali'] = array(
    '#type' => 'fieldset',
    '#title' => t('Impostazioni importazione'),
    '#collapsible' => TRUE,
  );

  $form['impostazioni_generali']['test'] = array(
    '#type' => 'checkbox',
    '#title' => t('Impostazione di test (limita a 10 risultati)'),
  );

  foreach (migrando_entities_list() as $entity_type => $bundles) {
    $form['gestione_' . $entity_type] = array(
      '#type' => 'fieldset',
      '#title' => t('Gestione ' . $entity_type),
      '#collapsible' => TRUE,
    );

    $options = array(
      $entity_type => $entity_type,
    );

    foreach ($bundles as $bundle) {
      $form['gestione_' . $entity_type][$bundle] = array(
        '#type' => 'submit',
        '#value' => t('Aggiorna ' . $bundle),
        '#submit' => array('_submit_aggiorna_entity'),
      );
    }

    $form['extra'] = array(
      '#type' => 'fieldset',
      '#title' => t('Contenuti extra'),
      '#collapsible' => TRUE,
    );

    $form['extra']['flag'] = array(
      '#type' => 'submit',
      '#value' => t('Aggiorna flag'),
      '#submit' => array('_submit_aggiorna_flag'),
    );

    $form['extra']['hybridauth'] = array(
      '#type' => 'submit',
      '#value' => t('Aggiorna hybridauth'),
      '#submit' => array('_submit_aggiorna_hybridauth'),
    );

    $form['extra']['commenti'] = array(
      '#type' => 'submit',
      '#value' => t('Aggiorna commenti'),
      '#submit' => array('_submit_aggiorna_commenti'),
    );

    $form['extra']['converti_media'] = array(
      '#type' => 'submit',
      '#value' => t('Converti campi media'),
      '#submit' => array('_submit_aggiorna_converti_media'),
    );
  }

  return system_settings_form($form);
}

function _submit_aggiorna_commenti($form, &$form_state) {

  $page = 0;
  while (count(migrando_get_contents('comment', NULL, $page)) > 0) {
    $fetch = migrando_get_contents('comment', NULL, $page);
    foreach ($fetch as $single) {
      $uuids[] = $single->uuid;
    }
    $page++;
  }

  batch_set(_batch_aggiorna_commenti($uuids));
}

function _submit_aggiorna_convert_media($form, &$form_state) {
  batch_set(_batch_aggiorna_converti_media('node', 'canto', NULL));
}

function _batch_aggiorna_converti_media($entity_type, $bundle, $test) {
  $entity_ids = ildeposito_utils_get_entity('node', 'canto');

  foreach ($entity_ids as $entity_id) {
    $operations[] = array('_batch_entity_converti_media', array($entity_id));
    $batch = array(
      'operations' => $operations,
      'finished' => '_batch_entities_finished',
    );
  }
  return $batch;
}

/**
 * Batch operation: associate audio tiles to 1 node.
 * This is the function that is called on each operation in the above.
 */
function _batch_entity_converti_media($entity_id, &$context) {
  $context['results'][] = $entity_id;

  $node = reset(entity_load('node', array($entity_id)));

  if (count($node->field_risorse_audio_video) > 0) {
    foreach ($node->field_risorse_audio_video[LANGUAGE_NONE] as $key => $value) {
      $url = $value['url'];
      if (_is_media($url)) {
        $filename = $url;
        if ($value['title'] != '') {
          $filename = $value['title'];
        }

        $values = array(
          'uid' => $node->uid,
          'filemime' => 'video/youtube',
          'filename' => $filename,
          'filesize' => '0',
          'status' => '1',
          'timestamp' => time(),
          'type' => 'video',
          'uri' => $url,
        );

        $file = entity_create('file', $values);
        entity_save('file', $file);
        $file->display = 1;
        $node->field_media[LANGUAGE_NONE][] = (array) $file;
        unset($node->field_risorse_audio_video[LANGUAGE_NONE][$key]);
      } else {
        $node->field_links[LANGUAGE_NONE][] = $value;
      }
    }

    entity_save('node', $node);
  }
}

function is_media($url) {
  $return = FALSE;
  if (strpos($url, 'youtu') !== FALSE) {
    $return = TRUE;
  }
  return $return;
}


function _batch_aggiorna_commenti($uuids) {
  foreach ($uuids as $uuid) {

    // prendere il singolo commento
    $url = MIGRANDO_API . 'api/comment/' . $uuid;
    $oauth = migrando_authentication();
    $data = $oauth->fetch($url);
    $response_info = $oauth->getLastResponse();
    $response = json_decode($response_info);

    if (is_object($response)) {
      $operations[] = array('_batch_commento', array($response, $uuid));
    }

    $batch = array(
      'operations' => $operations,
      'finished' => '_batch_entities_finished',
    );
  }
  return $batch;
}

/**
 * Batch operation: create flags
 * This is the function that is called on each operation in the above.
 */
function _batch_commento($response, $uuid, &$context) {
  $context['results'][] = $uuid;

  // prendere il "pid" del commento padre (se esiste)
  $pid = 0;
  if ($response->pid != 0) {
    $url = MIGRANDO_API . 'api/comment_pid/' . $response->pid;
    $oauth = migrando_authentication();
    $data = $oauth->fetch($url);
    $risposta_info = $oauth->getLastResponse();
    $risposta = json_decode($risposta_info);
    $pid = $risposta[0];
  }

  $uid = reset(entity_get_id_by_uuid('user', array($response->uid)));
  $nid = reset(entity_get_id_by_uuid('node', array($response->nid)));

  $comment = new stdClass();
  $comment->nid = $nid; // nid of a node you want to attach a comment to
  $comment->cid = 0; // leave it as is
  $comment->pid = $pid; // parent comment id, 0 if none
  $comment->uid = $uid; // user's id, who left the comment
  $comment->mail = $response->mail;
  $comment->name = $response->name;
  $comment->thread = $response->thread;
  $comment->hostname = $response->hostname;
  $comment->created = $response->created;
  $comment->is_anonymous = 0; // leave it as is
  $comment->homepage = $response->homepage;
  $comment->status = COMMENT_PUBLISHED; // We auto-publish this comment
  $comment->language = LANGUAGE_NONE; // The same as for a node
  $comment->subject = $response->subject;
//  $comment->comment_body[LANGUAGE_NONE][0]['value'] = $response->comment_body[LANGUAGE_NONE][0]['value'];
//  $comment->comment_body[LANGUAGE_NONE][0]['format'] = $response->comment_body[LANGUAGE_NONE][0]['format'];
  //comment_submit($comment); // saving a comment
  //comment_save($comment);

  $a = 1;
}

function _submit_aggiorna_flag($form, &$form_state) {
  $result = db_query('SELECT uuid FROM {users}');
  foreach ($result as $record) {
    $uuids[] = $record->uuid;
  }

  batch_set(_batch_aggiorna_flag($uuids));
}


function _submit_aggiorna_hybridauth($form, &$form_state) {
  $result = db_query('SELECT uuid FROM {users}');
  foreach ($result as $record) {
    $uuids[] = $record->uuid;
  }

  batch_set(_batch_aggiorna_hybridauth($uuids));
}

function _batch_aggiorna_flag($uuids) {
  foreach ($uuids as $uuid) {
    $url = MIGRANDO_API . 'api/flag_users/' . $uuid;
    $oauth = migrando_authentication();
    $data = $oauth->fetch($url);
    $response_info = $oauth->getLastResponse();
    $response = json_decode($response_info);

   if (is_object($response)) {
     $operations[] = array('_batch_flag', array($response, $uuid));
   }

    $batch = array(
      'operations' => $operations,
      'finished' => '_batch_entities_finished',
    );
  }
  return $batch;
}

function _batch_aggiorna_hybridauth($uuids) {
  foreach ($uuids as $uuid) {
    $url = MIGRANDO_API . 'api/hybridauth_get/' . $uuid;
    $oauth = migrando_authentication();
    $data = $oauth->fetch($url);
    $response_info = $oauth->getLastResponse();
    $response = json_decode($response_info);
    $operations[] = array('_batch_hybridauth', array($response, $uuid));
    $batch = array(
      'operations' => $operations,
      'finished' => '_batch_entities_finished',
    );
  }
  return $batch;
}

/**
 * Batch operation: create flags
 * This is the function that is called on each operation in the above.
 */
function _batch_flag($flags, $uuid, &$context) {
  $context['results'][] = $uuid;

  $uid = reset(entity_get_id_by_uuid('user', array($uuid)));
  $account = user_load($uid);

  foreach ((array) $flags as $flag_name => $flag_objects) {
    foreach ($flag_objects as $flag_object) {
      $result = db_query('SELECT nid FROM {node} WHERE uuid = :uuid', array(':uuid' => $flag_object->node_uuid));
      foreach ($result as $record) {
        $nid = $record->nid;
      }

     flag('flag', $flag_object->flag_name, $nid, $account, FALSE);
    }
  }
}

/**
 * Batch operation: create flags
 * This is the function that is called on each operation in the above.
 */
function _batch_hybridauth($objects, $uuid, &$context) {
  $context['results'][] = $uuid;

  $result = db_query('SELECT uid FROM {users} WHERE uuid = :uuid', array(':uuid' => $uuid));
  foreach ($result as $record) {
    $uid = $record->uid;
  }

  foreach ($objects as $object) {
    $hybridauth = db_insert('hybridauth_identity')->fields(array(
        'uid' => $uid,
        'provider' => $object->provider,
        'provider_identifier' => $object->provider_identifier,
        'data' => $object->data,
      ))
    ->execute();
  }
}

function _submit_aggiorna_entity($form, &$form_state) {
  $bundle = end(explode(' ', $form_state['values']['op']));
  $entity_type = migrando_entity_type($bundle);
  if ($form_state['values']['test'] == 1) {
    $test = TRUE;
  }
  else {
    $test = FALSE;
  }
  batch_set(_batch_aggiorna_entities($entity_type, $bundle, $test));
}

function _batch_aggiorna_entities($entity_type, $bundle, $test) {
  $uuids = _entity_get_uuids($entity_type, $bundle);
  if ($test) {
    $uuids = array_slice($uuids, 0, 2);
  }
  foreach ($uuids as $uuid) {
    $operations[] = array('_batch_entity', array($entity_type, $bundle, $uuid));
    $batch = array(
      'operations' => $operations,
      'finished' => '_batch_entities_finished',
    );
  }
  return $batch;
}

/**
 * Batch operation: associate audio tiles to 1 node.
 * This is the function that is called on each operation in the above.
 */
function _batch_entity($entity_type, $bundle, $uuid, &$context) {
  $context['results'][] = $uuid;

  $entity_id = entity_get_id_by_uuid($entity_type, array($uuid));

  if ($entity_type == 'user') {
    $parameters['auth'] = TRUE;
  };

  if (count($entity_id) == 0) {
    $result = migrando_get_content($entity_type, $uuid);
    if (isset($result)) {
      $function = '_entity_fill_' . $entity_type;
      if (function_exists($function)) {
        $function($entity_type, $bundle, $uuid, $result, NULL);
      }
    }
  }
  else {
    $entity_id = reset($entity_id);
    $entity = reset(entity_load($entity_type, array($entity_id)));
    $result = migrando_get_content($entity_type, $uuid);
    switch ($entity_type) {

      case 'file':
        $function = '_entity_fill_' . $entity_type;
        if (function_exists($function)) {
          $function($entity_type, $bundle, $uuid, $result, $entity);
        }
        break;

      case 'user':
        $function = '_entity_fill_' . $entity_type;
        if (function_exists($function)) {
          $function($entity_type, $bundle, $uuid, $result, $entity);
        }
        break;

      case 'taxonomy_term':
        $function = '_entity_fill_' . $entity_type;
        if (function_exists($function)) {
          $function($entity_type, $bundle, $uuid, $result, $entity);
        }
        break;

      case 'node';
        $function = '_entity_fill_' . $entity_type;
        if (function_exists($function)) {
          $function($entity_type, $bundle, $uuid, $result, $entity);
        }
        break;
    }
  }

  //$fetch = json_decode(file_get_contents(MIGRANDO_API . 'api/' . $entity_type . '/' . $element->id));
}

/**
 *
 * @param type $success
 * @param type $results
 * @param type $operations
 */
function _batch_entities_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('@count entità processate.', array('@count' => count($results))));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array(
      '@operation' => $error_operation[0],
      '@args' => print_r($error_operation[0], TRUE)
    )));
  }
}
