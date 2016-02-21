<?php
/**
 * Created by PhpStorm.
 * User: sergej
 * Date: 26/03/15
 * Time: 21.33
 */

class mapperContainer {

  /**
   * @param type $bundle
   * @return string
   */
  public static function getEntityTypeList() {
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
    return $entities;
  }

  /**
   * Returns entity type by bundle
   * @param $bundle
   * @return mixed
   */
  public static function getEntityTypeByBundle($bundle) {
    $entity_types = self::getEntityTypeList();
    return $entity_types[$bundle];
  }

  /**
   *
   * @param type $bundle
   * @return array
   */
  public static function getEntityFields($entity_type, $bundle) {

    $fields['file'] = array(
      'image' => array(
        new fieldTypeValues('origfield', 'destfield', 'type'),
        new fieldTypeRef('origfield', 'destfield', 'type', 'entyitrf','tif'),
      ),
    );
    return $fields[$entity_type][$bundle];
  }
}