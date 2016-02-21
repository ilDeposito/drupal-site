<?php

/**
 * @file
 */

/**
 * Return entities ID
 */
function ildeposito_utils_get_entity($entity_type, $bundle = NULL, $column = NULL, $value = NULL, $field = NULL, $status = NULL, $property_order_by = NULL) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type);

  if ($field && $value && $column) {
    $query->fieldCondition($field, $column, $value, '=');
  }

  if ($bundle) {
    $query->entityCondition('bundle', $bundle);
  }

  if ($status) {
    $query->propertyCondition('status', $status);
  }

  if (is_array($property_order_by)) {
    list($column_ord, $direction_ord) = $property_order_by;
    $query->propertyOrderBy($column_ord, $direction_ord);
  }

  $result = $query->execute();
  $entity_ids = array();

  if (isset($result[$entity_type])) {
    foreach (array_keys($result[$entity_type]) as $entity_id) {
      $entity_ids[] = $entity_id;
    }
  }

  return $entity_ids;
}



/**
 * Recupera il title in base al nid
 * @param type $nid
 */
function wcap_utils_get_title($nid) {
  $title = FALSE;
  $query = db_select('node', 'n');
  $query->condition('n.nid', $nid, '=');
  $query->fields('n', array('title'));
  $result = $query->execute()->fetchAll();
  $title = $result[0]->title;
  return $title;
}