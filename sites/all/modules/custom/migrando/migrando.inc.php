<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * 
 * @param type $entity_type
 * @param type $bundle
 * @return type
 */
function _entity_get_uuids($entity_type, $bundle) {
  switch ($entity_type) {
    case 'taxonomy_term':
      $source_vid = reset(migrando_vocabulary('vid', $bundle));
      $parameters = array(
        'parameters' => 'parameters[vid]=' . $source_vid . '&',
      );
      break;

    case 'node':
      $parameters = array(
        'parameters' => 'parameters[type]=' . $bundle . '&',
      );
      break;
    
    case 'user':
      $parameters = NULL;
      break;

    case 'file':
      $parameters = array(
        'parameters' => 'parameters[type]=' . $bundle . '&',
      );
      break;
  }

  $page = 0;

  while (count(migrando_get_contents($entity_type, $parameters, $page)) > 0) {
    $fetch = migrando_get_contents($entity_type, $parameters, $page);
    foreach ($fetch as $single) {
      $uuids[] = $single->uuid;
    }
    $page++;
  }
  return $uuids;
}

/**
 * 
 * @param type $entity_type
 * @param type $bundle
 * @param type $uuid
 * @param type $result
 * @param type $entity
 */
function _entity_fill_taxonomy_term($entity_type, $bundle, $uuid, $result, $entity = NULL) {
  if (!$entity) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($bundle);
    $values = array(
      'uuid' => $uuid,
      'vocabulary_machine_name' => reset(migrando_vocabulary('voc_name', $result->vocabulary_machine_name)),
      'vid' => $vocabulary->vid,
      'format' => filtered_html,
    );
    $entity = entity_create($entity_type, $values);
  }
  _entity_fill_taxonomy_term_values($entity, $bundle, $result);
  $fields = migrando_entity_field_taxonomy($bundle);
  _entity_fill_entity_fields($fields, $entity, $bundle, $result);
  entity_save($entity_type, $entity);
}

/**
 * 
 * @param type $entity_type
 * @param type $bundle
 * @param type $uuid
 * @param type $result
 * @param type $entity
 */
function _entity_fill_node($entity_type, $bundle, $uuid, $result, $entity = NULL) {
  if (!$entity) {
    $values = array(
      'uuid' => $uuid,
      'type' => $bundle,
      'created' => $result->created,
    );
    $entity = entity_create($entity_type, $values);

    _entity_fill_node_values($entity, $bundle, $result);
    $fields = migrando_entity_field_node($bundle);
    _entity_fill_entity_fields($fields, $entity, $bundle, $result);

    try {
      entity_save($entity_type, $entity);
    } catch (Exception $exc) {
      watchdog('ImportilDeposito', $uuid);
    }

  }
  else /* if ($entity->changed->value() < $result->changed) */ {
    _entity_fill_node_values($entity, $bundle, $result);
    $fields = migrando_entity_field_node($bundle);
    _entity_fill_entity_fields($fields, $entity, $bundle, $result);
    try {
      entity_save($entity_type, $entity);
    } catch (Exception $exc) {
      watchdog('ImportilDeposito', $uuid);
    }
  }
}


/**
 * 
 * @param type $entity_type
 * @param type $bundle
 * @param type $uuid
 * @param type $result
 * @param type $entity
 */
function _entity_fill_user($entity_type, $bundle, $uuid, $result, $entity = NULL) {
  if (!$entity) {
    $values = array(
      'uuid' => $uuid,
      'name' => $result->name,
      'created' => $result->created,
      'mail' => $result->mail,
      'status'=> $result->status,
      'access'=> $result->access,
      'login'=> $result->login,      
    );
    $entity = entity_create($entity_type, $values);
    //$entity->roles->set('community');

    //_entity_fill_user_values($entity, $bundle, $result);
    //$fields = migrando_entity_field_node($bundle);
    //_entity_fill_entity_fields($fields, $entity, $bundle, $result);
    if ($result->name != '') {
      entity_save($entity_type, $entity);

      $a = 1;
    }
  }
  else /* if ($entity->changed->value() < $result->changed) */ {
    //_entity_fill_node_values($entity, $bundle, $result);
    //$fields = migrando_entity_field_node($bundle);
    //_entity_fill_entity_fields($fields, $entity, $bundle, $result);
    if ($result->name != '') {
      entity_save($entity_type, $entity);
    }
  }
}

/**
 * 
 * @param type $entity_type
 * @param type $bundle
 * @param type $uuid
 * @param type $result
 * @param type $entity
 */
function _entity_fill_file($entity_type, $bundle, $uuid, $result, $entity = NULL) {
  if (!$entity) {

    $author = reset(entity_get_id_by_uuid('user', array($result->uid)));


    if ($result->filemime == 'video/youtube' || $result->filemime == 'video/vimeo') {

      $url = MIGRANDO_API . 'api/media_uri/' . $uuid;
      $oauth = migrando_authentication();
      $data = $oauth->fetch($url);
      $response_info = $oauth->getLastResponse();
      $response = json_decode($response_info);

      $a = 1;

      $values = array(
        'uuid' => $uuid,
        'uid' => $author,
        'filemime' => $result->filemime,
        'filename' => $result->filename,
        'filesize' => $result->filesize,
        'status' => $result->status,
        'timestamp' => $result->timestamp,
        'alt' => $result->alt,
        'title' => $result->title,
        'type' => $result->type,
        'uri' => $response[0],
      );


    } else {
      $file = drupal_http_request(MIGRANDO_FILES . rawurlencode($result->filename));
      $filename_clean = transliteration_clean_filename($result->filename);
      file_unmanaged_save_data($file->data, 'public://immagini/' . $filename_clean);
      $values = array(
        'uuid' => $uuid,
        'uid' => $author,
        'filemime' => $result->filemime,
        'filename' => $filename_clean,
        'filesize' => $result->filesize,
        'timestamp' => $result->timestamp,
        'alt' => $result->alt,
        'title' => $result->title,
        'status' => $result->status,
        'type' => $bundle,
        'uri' => 'public://immagini/' . $filename_clean,
      );

      }


    $entity = entity_create($entity_type, $values);
  }
  _entity_fill_file_values($entity, $bundle, $result);
  $fields = migrando_entity_field_file($bundle);
  _entity_fill_entity_fields($fields, $entity, $bundle, $result);
  entity_save($entity_type, $entity);
}

/**
 * 
 * @param type $entity
 * @param type $bundle
 * @param type $result
 */
function _entity_fill_taxonomy_term_values($entity, $bundle, $result) {
  $entity->name = $result->name;
  $entity->weight = $result->weight;
  if ($result->description != '') {
    $entity->description = $result->description;
  }
}

/**
 * 
 * @param type $entity
 * @param type $bundle
 * @param type $result
 */
function _entity_fill_node_values($entity, $bundle, $result) {
  $entity->uid = '1';
  $entity->title = $result->title;
  $entity->log = -$result->log;
  $entity->status = $result->status;
  $entity->comment = $result->comment;
  $entity->promote = $result->promote;
  $entity->sticky = $result->stick;
}

/**
 * 
 * @param type $entity
 * @param type $bundle
 * @param type $result
 */
function _entity_fill_file_values($entity, $bundle, $result) {
  
}

/**
 *
 * @param type $fields
 * @param type $entity
 * @param type $bundle
 * @param type $result 
 */
function _entity_fill_entity_fields($fields, $entity, $bundle, $result) {
  foreach ($fields as $orig_field => $dest) {
    switch ($dest['type']) {
      case 'text':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['value'] = $value->value;
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['safe_value'] = $value->safe_value;
          }
        }
        else {
          unset($entity->{$dest}['field']);
        }
        break;

      case 'text_long':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['value'] = $value->value;
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['safe_value'] = $value->value;
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['format'] = $dest['format'];
          }
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;

      case 'link':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['url'] = $value->url;
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['title'] = $value->title;
          }
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;

      case 'file':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            unset($fid, $file);
            $fid = reset(entity_get_id_by_uuid('file', array($value->uuid)));
            if ($fid > 0) {
              $file = file_load($fid);
              $entity->{$dest['field']}[LANGUAGE_NONE][$key] = (array) $file;
              $entity->{$dest['field']}[LANGUAGE_NONE][$key]['display'] = 1;
            }
          }
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;

      case 'email':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            $entity->{$dest['field']}[LANGUAGE_NONE][$key]['email'] = $value->email;
          }
        }
        else {
          unset($entity->{$dest}['field']);
        }
        break;

      case 'tags':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            unset($tid);
            $tid = reset(entity_get_id_by_uuid($dest['entity_type'], array($value->tid)));
            if ($tid > 0) {
              try {
                $entity->{$dest['field']}[LANGUAGE_NONE][$key]['tid'] = $tid;
              } catch (EntityMetadataWrapperException $exc) {
                watchdog('ImportilDeposito', $result->uuid . ' - ' . $result->nid);
              }


            }
          }
        }
        else {
          unset($entity->{$dest['field']});
        }

        break;

      case 'ref':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          foreach ($result->$orig_field->und as $key => $value) {
            unset($target_id);
            $target_id = entity_get_id_by_uuid($dest['entity_type'], array($value->{$dest['target']}));
            if ($target_id > 0) {
              try {
                $entity->{$dest['field']}[LANGUAGE_NONE][$key]['target_id'] = reset($target_id);
              } catch (EntityMetadataWrapperException $exc) {
                watchdog('ImportilDeposito', $result->uuid . ' - ' . $result->nid);
              }
            }
          }
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;

      case 'geofield':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          unset($values);
          $values = array(
            'lat' => $result->$orig_field->und[0]->lat,
            'lon' => $result->$orig_field->und[0]->lon,
          );
          $entity->{$dest['field']}[LANGUAGE_NONE][] = geofield_compute_values($values, 'latlon');
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;

      case 'date':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          $entity->{$dest['field']}[LANGUAGE_NONE][] = (array) $result->$orig_field->und[0];
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;

      case 'addressfield':
        if (count($result->$orig_field->und) > 0) {
          unset($entity->{$dest['field']});
          $entity->{$dest['field']}[LANGUAGE_NONE][] = (array) $result->$orig_field->und[0];
        }
        else {
          unset($entity->{$dest['field']});
        }
        break;
    }
  }
}
