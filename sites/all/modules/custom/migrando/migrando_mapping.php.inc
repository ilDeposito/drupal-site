<?php

/**
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Mapping vocabolari
 * $key = vocabolario sorgente
 * $value = vocabolario destinazione
 */
function migrando_vocabulary($type, $search = NULL) {
  $vid = array(
    '6' => 'sezioni',
    '1' => 'tags',
    '2' => 'lingue',
    '3' => 'localizzazioni',
    '4' => 'percorsi',
    '9' => 'tipi_libreria',
    '10' => 'tipi_gruppi',
  );

  $voc_name = array(
    'sezioni' => 'sezioni',
    'tags' => 'tags',
    'lingue' => 'lingue',
    'localizzazione' => 'localizzazioni',
    'percorsi' => 'percorsi',
    'tipo_libreria' => 'tipi_libreria',
    'tipi_gruppi' => 'tipi_gruppi',
  );

  switch ($type) {
    case 'vid':
      $array = $vid;
      break;

    case 'voc_name':
      $array = $voc_name;
      break;
  }

  if (!$search) {
    return $array;
  }
  else {
    return array_keys($array, $search);
  }
}

/**
 * 
 * @return array
 */
function migrando_entities_list() {
  $entities = array(
    'node' => array('evento', 'canto', 'autore', 'articolo', 'traduzione', 'voce_libreria', 'pagina', 'gruppi'),
    'taxonomy_term' => array('sezioni', 'tags', 'lingue', 'localizzazioni', 'percorsi', 'tipi_libreria', 'tipi_gruppi'),
    'file' => array('image', 'video'),
    'user' => array('user'),
  );
  return $entities;
}

/**
 * 
 * @param type $bundle
 * @return string
 */
function migrando_entity_type($bundle) {
  $entities = array(
    'evento' => 'node',
    'canto' => 'node',
    'autore' => 'node',
    'articolo' => 'node',
    'traduzione' => 'node',
    'voce_libreria' => 'node',
    'gruppi' => 'node',
    'pagina' => 'node',
    'sezioni' => 'taxonomy_term',
    'tags' => 'taxonomy_term',
    'lingue' => 'taxonomy_term',
    'localizzazioni' => 'taxonomy_term',
    'percorsi' => 'taxonomy_term',
    'tipi_libreria' => 'taxonomy_term',
    'tipi_gruppi' => 'taxonomy_term',
    'image' => 'file',
    'video' => 'file',
    'user' => 'user',
  );
  return $entities[$bundle];
}

/**
 * 
 * @param type $bundle
 * @return array
 */
function migrando_entity_field_taxonomy($bundle) {
  $fields['sezioni'] = array(
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
    'field_periodo' => array(
      'field' => 'field_periodo',
      'type' => 'text',
    ),
  );
  $fields['percorsi'] = array(
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
  );
  $fields['tags'] = array(
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
  );
  $fields['localizzazioni'] = array(
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
  );

  $fields['lingue'] = array(
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
  );
  $fields['tipi_libreria'] = array();

  $fields['tipi_gruppi'] = array();
  return $fields[$bundle];
}

/**
 * 
 * @param type $bundle
 * @return array
 */
function migrando_entity_field_user($bundle) {
  $fields = array();
  return $fields[$bundle];
}

/**
 * 
 * @param type $bundle
 * @return array
 */
function migrando_entity_field_file($bundle) {
  $fields['image'] = array(
    'field_file_image_alt_text' => array(
      'field' => 'field_file_image_alt_text',
      'type' => 'text',
    ),
    'field_file_image_title_text' => array(
      'field' => 'field_file_image_title_text',
      'type' => 'text',
    ),
    'field_links' => array(
      'field' => 'field_links',
      'type' => 'link',
    ),
    'field_fonte_text' => array(
      'field' => 'field_informazioni',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
  );
  return $fields[$bundle];
}

/**
 * 
 * @param type $bundle
 * @return array
 */
function migrando_entity_field_node($bundle) {
  $fields['articolo'] = array(
    'body' => array(
      'field' => 'field_testo',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
    'field_tags' => array(
      'field' => 'field_tags',
      'type' => 'tags',
      'entity_type' => 'taxonomy_term',
    ),
    /* 'field_collegamenti' => array(
      'field' => 'field_links',
      'type' => 'link',
      ), */
  );

  $fields['autore'] = array(
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
    'field_nome' => array(
      'field' => 'field_nome',
      'type' => 'text',
    ),
    'field_cognome' => array(
      'field' => 'field_cognome',
      'type' => 'text',
    ),
    'field_altri_nomi' => array(
      'field' => 'field_altri_nomi',
      'type' => 'text',
    ),
    'field_sezione' => array(
      'field' => 'field_sezione',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_localizzazione' => array(
      'field' => 'field_localizzazione',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_tags' => array(
      'field' => 'field_tags',
      'type' => 'tags',
      'entity_type' => 'taxonomy_term',
    ),
    'field_links' => array(
      'field' => 'field_links',
      'type' => 'link',
    ),
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
  );

  $fields['canto'] = array(
    'field_informazioni' => array(
      'field' => 'field_informazioni',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
    'field_capoverso' => array(
      'field' => 'field_capoverso',
      'type' => 'text',
    ),
    'field_titolo_alt' => array(
      'field' => 'field_titolo_alt',
      'type' => 'text',
    ),
    'field_anno' => array(
      'field' => 'field_anno',
      'type' => 'date',
    ),
    'field_testo' => array(
      'field' => 'field_testo',
      'type' => 'text_long',
      'format' => 'plain_text',
    ),
    'field_accordi' => array(
      'field' => 'field_accordi',
      'type' => 'text_long',
      'format' => 'plain_text',
    ),
    'field_sezione' => array(
      'field' => 'field_sezione',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_autore_testo' => array(
      'field' => 'field_autore_testo',
      'type' => 'ref',
      'entity_type' => 'node',
      'target' => 'nid',
    ),
    'field_autore_musica' => array(
      'field' => 'field_autore_musica',
      'type' => 'ref',
      'entity_type' => 'node',
      'target' => 'nid',
    ),
    'field_tags' => array(
      'field' => 'field_tags',
      'type' => 'tags',
      'entity_type' => 'taxonomy_term',
    ),
    'field_lingua' => array(
      'field' => 'field_lingua',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_link_audio' => array(
      'field' => 'field_risorse_audio_video',
      'type' => 'link',
    ),
    'field_links' => array(
      'field' => 'field_links',
      'type' => 'link',
    ),
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
  );

  $fields['evento'] = array(
    'field_informazioni' => array(
      'field' => 'field_testo',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
    'field_sezione' => array(
      'field' => 'field_sezione',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_localizzazione' => array(
      'field' => 'field_localizzazione',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_percorso' => array(
      'field' => 'field_percorso',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_tags' => array(
      'field' => 'field_tags',
      'type' => 'tags',
      'entity_type' => 'taxonomy_term',
    ),
    'field_canti_evento' => array(
      'field' => 'field_canti_collegati',
      'type' => 'ref',
      'entity_type' => 'node',
      'target' => 'nid',
    ),
    'field_links' => array(
      'field' => 'field_links',
      'type' => 'link',
    ),
    'field_geofield' => array(
      'field' => 'field_geofield',
      'type' => 'geofield',
    ),
    'field_data_evento' => array(
      'field' => 'field_data_evento',
      'type' => 'date',
    ),
  );

  $fields['pagina'] = array(
    'body' => array(
      'field' => 'field_testo',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
  );

  $fields['traduzione'] = array(
    'field_testo' => array(
      'field' => 'field_testo',
      'type' => 'text_long',
      'format' => 'plain_text',
    ),
    'field_informazioni' => array(
      'field' => 'field_informazioni',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
    'field_canto_riferimento' => array(
      'field' => 'field_canti_collegati',
      'type' => 'ref',
      'entity_type' => 'node',
      'target' => 'nid',
    ),
    'field_sezione' => array(
      'field' => 'field_sezione',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_lingua' => array(
      'field' => 'field_lingua',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_lingua_originale' => array(
      'field' => 'field_lingua_originale',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_old_id' => array(
      'field' => 'field_old_id',
      'type' => 'text',
    ),
  );

  $fields['voce_libreria'] = array(
    'field_informazioni' => array(
      'field' => 'field_informazioni',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
    'field_links' => array(
      'field' => 'field_links',
      'type' => 'link',
    ),
    'field_collana' => array(
      'field' => 'field_collana',
      'type' => 'text',
    ),
    'field_a_cura_di' => array(
      'field' => 'field_a_cura_di',
      'type' => 'boolean',
    ),
    'field_autore' => array(
      'field' => 'field_autori_voce',
      'type' => 'text',
    ),
    'field_editore' => array(
      'field' => 'field_editore',
      'type' => 'text',
    ),
    'field_citta' => array(
      'field' => 'field_citta',
      'type' => 'text',
    ),
    'field_anno' => array(
      'field' => 'field_anno',
      'type' => 'date',
    ),
    'field_autori_correlati' => array(
      'field' => 'field_autori_collegati',
      'type' => 'ref',
      'entity_type' => 'node',
      'target' => 'nid',
    ),
    'field_tipo_voce' => array(
      'field' => 'field_tipo_voce',
      'type' => 'tags',
      'entity_type' => 'taxonomy_term',
      'target' => 'tid',
    ),
    'field_tags' => array(
      'field' => 'field_tags',
      'type' => 'tags',
      'entity_type' => 'taxonomy_term',
    ),
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
  );

  $fields['gruppi'] = array(
    'body' => array(
      'field' => 'field_informazioni',
      'type' => 'text_long',
      'format' => 'filtered_html',
    ),
    'field_links' => array(
      'field' => 'field_links',
      'type' => 'link',
    ),
    'field_email' => array(
      'field' => 'field_email',
      'type' => 'email',
    ),
    'field_citta' => array(
      'field' => 'field_citta',
      'type' => 'text',
    ),
    'field_anno' => array(
      'field' => 'field_anno',
      'type' => 'date',
    ),
    'field_tipo_gruppo' => array(
      'field' => 'field_tipo_gruppo',
      'type' => 'ref',
      'entity_type' => 'taxonomy_term',
      'target' => 'target_id',
    ),
    'field_images' => array(
      'field' => 'field_immagine',
      'type' => 'file',
    ),
    'field_media' => array(
      'field' => 'field_media',
      'type' => 'file',
    ),
    'field_geofield' => array(
      'field' => 'field_geofield',
      'type' => 'geofield',
    ),
    'field_indirizzo' => array(
      'field' => 'field_indirizzo',
      'type' => 'addressfield',
    ),
  );

  return $fields[$bundle];
}
