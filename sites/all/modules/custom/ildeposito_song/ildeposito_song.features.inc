<?php
/**
 * @file
 * ildeposito_song.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_song_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ildeposito_song_node_info() {
  $items = array(
    'song' => array(
      'name' => t('Song'),
      'base' => 'node_content',
      'description' => t('Add a <em>song</em> to the archive.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
