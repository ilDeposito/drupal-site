<?php
/**
 * @file
 * class SongNodeWrapper
 */

class SongNodeWrapper extends WdNodeWrapper {

  protected $entity_type = 'node';
  private static $bundle = 'song';

  /**
   * Create a new song node.
   *
   * @param array $values
   * @param string $language
   * @return SongNodeWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('entity_type' => 'node', 'bundle' => self::$bundle, 'type' => self::$bundle);
    $entity_wrapper = parent::create($values, $language);
    return new SongNodeWrapper($entity_wrapper->value());
  }

  /**
   * Sets field_year
   *
   * @param $value
   *
   * @return $this
   */
  public function setYear($value) {
    $this->set('field_year', $value);
    return $this;
  }

  /**
   * Retrieves field_year
   *
   * @return mixed
   */
  public function getYear() {
    return $this->get('field_year');
  }

  /**
   * Sets field_section
   *
   * @param $value
   *
   * @return $this
   */
  public function setSection($value) {
    if (is_array($value)) {
      foreach ($value as $i => $v) {
        if ($v instanceof WdTaxonomyTermWrapper) {
          $value[$i] = $v->value();
        }
      }
    }
    else {
      if ($value instanceof WdTaxonomyTermWrapper) {
        $value = $value->value();
      }
    }

    $this->set('field_section', $value);
    return $this;
  }

  /**
   * Retrieves field_section
   *
   * @return SectionsTaxonomyTermWrapper[]
   */
  public function getSection() {
    $values = $this->get('field_section');
    foreach ($values as $i => $value) {
      $values[$i] = new SectionsTaxonomyTermWrapper($value);
    }
    return $values;
  }

  /**
   * Removes a value from field_section
   *
   * @param $value
   *   Value to remove.
   *
   * @return $this
   */
  function removeFromSection($value) {
    if ($value instanceof WdTaxonomyTermWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_section');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('taxonomy_term', $existing_value) == entity_id('taxonomy_term', $value)) {
          unset($existing_values[$i]);
        }
      }
    }
    $this->set('field_section', array_values($existing_values));
    return $this;
  }


  /**
   * Adds a value to field_section
   *
   * @param $value
   *
   * @return $this
   */
  public function addToSection($value) {
    if ($value instanceof WdTaxonomyTermWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_section');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('taxonomy_term', $existing_value) == entity_id('taxonomy_term', $value)) {
          return $this;  // already here
        }
      }
    }
    $existing_values[] = $value;
    $this->set('field_section', $existing_values);
    return $this;
  }

  /**
   * Sets field_tag
   *
   * @param $value
   *
   * @return $this
   */
  public function setTag($value) {
    $this->set('field_tag', $value);
    return $this;
  }

  /**
   * Retrieves field_tag
   *
   * @return mixed
   */
  public function getTag() {
    return $this->get('field_tag');
  }

  /**
   * Sets field_alternative_titles
   *
   * @param $value
   *
   * @return $this
   */
  public function setAlternativeTitles($value, $format = NULL) {
    $this->setText('field_alternative_titles', $value, $format);
    return $this;
  }

  /**
   * Retrieves field_alternative_titles
   *
   * @return mixed
   */
  public function getAlternativeTitles($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('field_alternative_titles', $format, $markup_format);
  }

  /**
   * Removes a value from field_author
   *
   * @param $value
   *   Value to remove.
   *
   * @return $this
   */
  function removeFromAuthor($value) {
    if ($value instanceof WdNodeWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_author');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('node', $existing_value) == entity_id('node', $value)) {
          unset($existing_values[$i]);
        }
      }
    }
    $this->set('field_author', array_values($existing_values));
    return $this;
  }


  /**
   * Adds a value to field_author
   *
   * @param $value
   *
   * @return $this
   */
  public function addToAuthor($value) {
    if ($value instanceof WdNodeWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_author');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('node', $existing_value) == entity_id('node', $value)) {
          return $this;  // already here
        }
      }
    }
    $existing_values[] = $value;
    $this->set('field_author', $existing_values);
    return $this;
  }

  /**
   * Sets field_music_author
   *
   * @param $value
   *
   * @return $this
   */
  public function setMusicAuthor($value) {
    if (is_array($value)) {
      foreach ($value as $i => $v) {
        if ($v instanceof WdNodeWrapper) {
          $value[$i] = $v->value();
        }
      }
    }
    else {
      if ($value instanceof WdNodeWrapper) {
        $value = $value->value();
      }
    }

    $this->set('field_music_author', $value);
    return $this;
  }

  /**
   * Retrieves field_music_author
   *
   * @return AuthorNodeWrapper[]
   */
  public function getMusicAuthor() {
    $values = $this->get('field_music_author');
    foreach ($values as $i => $value) {
      $values[$i] = new AuthorNodeWrapper($value);
    }
    return $values;
  }

  /**
   * Removes a value from field_music_author
   *
   * @param $value
   *   Value to remove.
   *
   * @return $this
   */
  function removeFromMusicAuthor($value) {
    if ($value instanceof WdNodeWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_music_author');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('node', $existing_value) == entity_id('node', $value)) {
          unset($existing_values[$i]);
        }
      }
    }
    $this->set('field_music_author', array_values($existing_values));
    return $this;
  }


  /**
   * Adds a value to field_music_author
   *
   * @param $value
   *
   * @return $this
   */
  public function addToMusicAuthor($value) {
    if ($value instanceof WdNodeWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_music_author');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('node', $existing_value) == entity_id('node', $value)) {
          return $this;  // already here
        }
      }
    }
    $existing_values[] = $value;
    $this->set('field_music_author', $existing_values);
    return $this;
  }

  /**
   * Sets field_language
   *
   * @param $value
   *
   * @return $this
   */
  public function setLanguage($value) {
    if (is_array($value)) {
      foreach ($value as $i => $v) {
        if ($v instanceof WdTaxonomyTermWrapper) {
          $value[$i] = $v->value();
        }
      }
    }
    else {
      if ($value instanceof WdTaxonomyTermWrapper) {
        $value = $value->value();
      }
    }

    $this->set('field_language', $value);
    return $this;
  }

  /**
   * Removes a value from field_language
   *
   * @param $value
   *   Value to remove.
   *
   * @return $this
   */
  function removeFromLanguage($value) {
    if ($value instanceof WdTaxonomyTermWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_language');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('taxonomy_term', $existing_value) == entity_id('taxonomy_term', $value)) {
          unset($existing_values[$i]);
        }
      }
    }
    $this->set('field_language', array_values($existing_values));
    return $this;
  }


  /**
   * Adds a value to field_language
   *
   * @param $value
   *
   * @return $this
   */
  public function addToLanguage($value) {
    if ($value instanceof WdTaxonomyTermWrapper) {
      $value = $value->value();
    }
    $existing_values = $this->get('field_language');
    if (!empty($existing_values)) {
      foreach ($existing_values as $i => $existing_value) {
        if (!empty($existing_value) && entity_id('taxonomy_term', $existing_value) == entity_id('taxonomy_term', $value)) {
          return $this;  // already here
        }
      }
    }
    $existing_values[] = $value;
    $this->set('field_language', $existing_values);
    return $this;
  }

  /**
   * Sets field_chords
   *
   * @param $value
   *
   * @return $this
   */
  public function setChords($value, $format = NULL) {
    $this->setText('field_chords', $value, $format);
    return $this;
  }

  /**
   * Retrieves field_chords
   *
   * @return mixed
   */
  public function getChords($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('field_chords', $format, $markup_format);
  }

  /**
   * Sets field_body
   *
   * @param $value
   *
   * @return $this
   */
  public function setBody($value, $format = NULL) {
    $this->setText('field_body', $value, $format);
    return $this;
  }

  /**
   * Retrieves field_body
   *
   * @return mixed
   */
  public function getBody($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('field_body', $format, $markup_format);
  }

  /**
   * Sets field_links
   *
   * @param $value
   *
   * @return $this
   */
  public function setLinks($value) {
    $this->set('field_links', $value);
    return $this;
  }

  /**
   * Retrieves field_links
   *
   * @return mixed
   */
  public function getLinks() {
    return $this->get('field_links');
  }

  /**
   * Sets field_source_link
   *
   * @param $value
   *
   * @return $this
   */
  public function setSourceLink($value) {
    $this->set('field_source_link', $value);
    return $this;
  }

  /**
   * Retrieves field_source_link
   *
   * @return mixed
   */
  public function getSourceLink() {
    return $this->get('field_source_link');
  }

  /**
   * Sets field_source_text
   *
   * @param $value
   *
   * @return $this
   */
  public function setSourceText($value, $format = NULL) {
    $this->setText('field_source_text', $value, $format);
    return $this;
  }

  /**
   * Retrieves field_source_text
   *
   * @return mixed
   */
  public function getSourceText($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('field_source_text', $format, $markup_format);
  }

  /**
   * Sets field_media
   *
   * @param $value
   *
   * @return $this
   */
  public function setMedia($value) {
    $this->set('field_media', $value);
    return $this;
  }

  /**
   * Retrieves field_media
   *
   * @return mixed
   */
  public function getMedia() {
    return $this->get('field_media');
  }

  /**
   * Retrieves field_media as a URL
   *
   * @param string $image_style
   *   (optional) Image style for the URL
   * @param bool $absolute
   *   Whether to return an absolute URL or not
   *
   * @return string[]
   */
  public function getMediaUrl($absolute = FALSE) {
    $files = $this->get('field_media');
    if (!empty($files)) {
      foreach ($files as $i => $file) {
        $files[$i] = url(file_create_url($file['uri']), array('absolute' => $absolute));
      }
    }
    return $files;
  }


}
