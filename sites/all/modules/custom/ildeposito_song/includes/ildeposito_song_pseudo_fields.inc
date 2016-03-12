<?php

/**
 * @file Callback function - pseudo fields for song content type
 */

/**
 * Callback function for related_event pseudo field
 * @param SongNodeWrapper $node_wrap
 * @return string
 */
function _ildeposito_song_related_event($node_wrap) {
  $output = '';
  $events_ids = ildeposito_utils_get_entity('node', 'event', 'field_related_songs', 'target_id', $node_wrap->getNid());
  if (!empty($events_ids)) {
    $events = entity_load('node', $events_ids);
    $output .= render(entity_view('node', $events, 'related_content'));
  }
  return FALSE;
}

/**
 * Callback function for translation pseudo field
 * @param SongNodeWrapper $node_wrap
 * @return string
 */
function _ildeposito_song_translation($node_wrap) {
  $output = '';
  return $output;
}

/**
 * Callback function for details pseudo field
 * @param SongNodeWrapper $node_wrap
 * @return string
 */
function _ildeposito_song_details($node_wrap) {
  $output = '';
  return $output;
}