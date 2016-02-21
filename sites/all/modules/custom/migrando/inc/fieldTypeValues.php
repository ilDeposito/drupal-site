<?php
/**
 * Created by PhpStorm.
 * User: sergej
 * Date: 26/03/15
 * Time: 21.53
 */

class fieldTypeValues {
  public function __construct($origField, $destField, $typeField) {
    $this->origField = $origField;
    $this->destField = $destField;
    $this->typeField = $typeField;
  }
}

class fieldTypeRef extends fieldTypeValues {
  public function __construct($origField, $destField, $typeField, $entityRef, $entityId) {
    parent::__construct($origField, $destField, $typeField);
    $this->entityRef = $entityRef;
    $this->entityId = $entityId;
  }
}