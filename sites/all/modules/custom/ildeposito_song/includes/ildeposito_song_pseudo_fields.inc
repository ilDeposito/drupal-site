<?php

/**
 * @file Callback function - pseudo fields for song
 */


/**
 * Callback function for related_event pseudo field
 * @param $node
 * @return string
 */
function _ildeposito_song_related_event($node) {
  $output = '';
  $events_ids = ildeposito_utils_get_entity('node', 'event', 'field_related_songs', 'target_id', $node->nid);
  if (!empty($events_ids)) {
    $events = entity_load('node', $events_ids);
    $output .= render(entity_view('node', $events, 'related_content'));
  }
  return $output;
}

/**
 * Callback function for translation pseudo field
 * @param $node
 * @return string
 */
function _ildeposito_song_translation($node) {
  $output = '';
  return $output;
}