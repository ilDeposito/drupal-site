<?php
/**
 * @file
 * ildeposito_song.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_song_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create song content'.
  $permissions['create song content'] = array(
    'name' => 'create song content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any song content'.
  $permissions['delete any song content'] = array(
    'name' => 'delete any song content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own song content'.
  $permissions['delete own song content'] = array(
    'name' => 'delete own song content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any song content'.
  $permissions['edit any song content'] = array(
    'name' => 'edit any song content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own song content'.
  $permissions['edit own song content'] = array(
    'name' => 'edit own song content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
