<?php

/**
 * @file
 * Contains the FeedsCSVParser class.
 */

/**
 * Parses a given file as a CSV file.
 */
class FeedsCSVParser extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $source_config = $source->getConfigFor($this);
    $state = $source->state(FEEDS_PARSE);

    // Load and configure parser.
    feeds_include_library('ParserCSV.inc', 'ParserCSV');
    $parser = new ParserCSV();
    $delimiter = $source_config['delimiter'] == 'TAB' ? "\t" : $source_config['delimiter'];
    $parser->setDelimiter($delimiter);

    $iterator = new ParserCSVIterator($fetcher_result->getFilePath());

    // Process header.
    if (!empty($source_config['header_size'])) {
      $skip = $source_config['header_size'];
      if (!empty($source_config['header_active']) && $source_config['header_active'] > 1) {
        $this->parseItems($parser, $iterator, 0, $source_config['header_active'] - 1);
        $parser->setStartByte($iterator->currentPos());

        $skip -= $source_config['header_active'];
      }

      $header = $this->parseHeader($parser, $iterator);
      if (!$header) {
        return;
      }
      $parser->setColumnNames($header);

      $this->parseItems($parser, $iterator, $iterator->currentPos(), $skip);
    }

    // Determine section to parse, parse.
    $start = $state->pointer ? $state->pointer : $parser->lastLinePos();
    $limit = $source->importer->getLimit();
    $rows = $this->parseItems($parser, $iterator, $start, $limit);

    // Report progress.
    $state->total = filesize($fetcher_result->getFilePath());
    $state->pointer = $parser->lastLinePos();
    $progress = $parser->lastLinePos() ? $parser->lastLinePos() : $state->total;
    $state->progress($state->total, $progress);

    // Create a result object and return it.
    return new FeedsParserResult($rows, $source->feed_nid);
  }

  /**
   * Get first line and use it for column names, convert them to lower case.
   * Be aware that the $parser and iterator objects can be modified in this
   * function since they are passed in by reference
   *
   * @param ParserCSV $parser
   * @param ParserCSVIterator $iterator
   * @return
   *   An array of lower-cased column names to use as keys for the parsed items.
   */
  protected function parseHeader(ParserCSV $parser, ParserCSVIterator $iterator) {
    $parser->setLineLimit(1);
    $rows = $parser->parse($iterator);
    if (!count($rows)) {
      return FALSE;
    }
    $header = array_shift($rows);
    foreach ($header as $i => $title) {
      $header[$i] = trim(drupal_strtolower($title));
    }
    return $header;
  }

  /**
   * Parse all of the items from the CSV.
   *
   * @param ParserCSV $parser
   * @param ParserCSVIterator $iterator
   * @return
   *   An array of rows of the CSV keyed by the column names previously set
   */
  protected function parseItems(ParserCSV $parser, ParserCSVIterator $iterator, $start = 0, $limit = 0) {
    $parser->setLineLimit($limit);
    $parser->setStartByte($start);
    $rows = $parser->parse($iterator);
    return $rows;
  }

  /**
   * Override parent::getMappingSources().
   */
  public function getMappingSources() {
    return FALSE;
  }

  /**
   * Override parent::getSourceElement() to use only lower keys.
   */
  public function getSourceElement(FeedsSource $source, FeedsParserResult $result, $element_key) {
    return parent::getSourceElement($source, $result, drupal_strtolower($element_key));
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array(
      'delimiter' => $this->config['delimiter'],
      'no_headers' => $this->config['no_headers'],
    );
  }

  /**
   * Source form.
   *
   * Show mapping configuration as a guidance for import form users.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['#weight'] = -10;

    $mappings = feeds_importer($this->id)->processor->config['mappings'];
    $sources = $uniques = array();
    foreach ($mappings as $mapping) {
      $sources[] = check_plain($mapping['source']);
      if ($mapping['unique']) {
        $uniques[] = check_plain($mapping['source']);
      }
    }

    $output = t('Import !csv_files with one or more of these columns: !columns.', array('!csv_files' => l(t('CSV files'), 'http://en.wikipedia.org/wiki/Comma-separated_values'), '!columns' => implode(', ', $sources)));
    $items = array();
    $items[] = format_plural(count($uniques), t('Column <strong>!column</strong> is mandatory and considered unique: only one item per !column value will be created.', array('!column' => implode(', ', $uniques))), t('Columns <strong>!columns</strong> are mandatory and values in these columns are considered unique: only one entry per value in one of these column will be created.', array('!columns' => implode(', ', $uniques))));
    $items[] = l(t('Download a template'), 'import/' . $this->id . '/template');
    $form['help']['#markup'] = '<div class="help"><p>' . $output . '</p>' . theme('item_list', array('items' => $items)) . '</div>';
    $form['delimiter'] = array(
      '#type' => 'select',
      '#title' => t('Delimiter'),
      '#description' => t('The character that delimits fields in the CSV file.'),
      '#options'  => array(
        ',' => ',',
        ';' => ';',
        'TAB' => 'TAB',
      ),
      '#default_value' => isset($source_config['delimiter']) ? $source_config['delimiter'] : ',',
    );
    $form['no_headers'] = array(
      '#type' => 'checkbox',
      '#title' => t('No Headers'),
      '#description' => t('Check if the imported CSV file does not start with a header row. If checked, mapping sources must be named \'0\', \'1\', \'2\' etc.'),
      '#default_value' => isset($source_config['no_headers']) ? $source_config['no_headers'] : 0,
    );

    $form['header_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Header size'),
      '#description' => t('How many rows are the header.'),
      '#default_value' => isset($source_config['header_size']) ? $source_config['header_size'] : $this->config['header_size'],
    );
    $form['header_active'] = array(
      '#type' => 'textfield',
      '#title' => t('Active header'),
      '#description' => t('Which header to use. If 0, mapping sources must be named \'0\', \'1\', \'2\' etc.'),
      '#default_value' => $this->config['header_active'],
      '#states' => array(
        'invisible' => array(
          ':input[name="feeds[FeedsCSVParser][header_size]"]' => array('value' => '0'),
        ),
      ),
    );

    return $form;
  }

  /**
   * Build configuration form validate.
   */
  public function sourceFormValidate(&$source_config) {
    if ($source_config['header_size'] > 0 && ($source_config['header_active'] > $source_config['header_size'])) {
      $message = t('Active header must be between 0 and %size', array('%size' => $source_config['header_size']));

      form_set_error('header_active', $message);
    }
  }

  /**
   * Define default configuration.
   */
  public function configDefaults() {
    return array(
      'delimiter' => ',',
      'no_headers' => 0,
      'header_size' => 1,
      'header_active' => 1,
    );
  }

  /**
   * Build configuration form.
   */
  public function configForm(&$form_state) {
    $form = array();

    $form['delimiter'] = array(
      '#type' => 'select',
      '#title' => t('Default delimiter'),
      '#description' => t('Default field delimiter.'),
      '#options' => array(
        ',' => ',',
        ';' => ';',
        'TAB' => 'TAB',
      ),
      '#default_value' => $this->config['delimiter'],
    );

    $form['header_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Header size'),
      '#description' => t('How many rows the header is. If 0, mapping sources must be named \'0\', \'1\', \'2\' etc.'),
      '#default_value' => $this->config['header_size'],
    );
    $form['header_active'] = array(
      '#type' => 'textfield',
      '#title' => t('Active header'),
      '#description' => t('Which header to use. If 0, mapping sources must be named \'0\', \'1\', \'2\' etc.'),
      '#default_value' => $this->config['header_active'],
      '#states' => array(
        'invisible' => array(
          ':input[name="header_size"]' => array('value' => '0'),
        ),
      ),
    );

    return $form;
  }

  /**
   * Build configuration form validate.
   */
  public function configFormValidate($form_state) {
    if ($form_state['header_size'] > 0 && ($form_state['header_active'] > $form_state['header_size'])) {
      $message = t('Active header must be between 0 and %size', array('%size' => $form_state['header_size']));

      form_set_error('header_active', $message);
    }
  }

  public function getTemplate() {
    $mappings = feeds_importer($this->id)->processor->config['mappings'];
    $sources = $uniques = array();
    foreach ($mappings as $mapping) {
      if ($mapping['unique']) {
        $uniques[] = check_plain($mapping['source']);
      }
      else {
        $sources[] = check_plain($mapping['source']);
      }
    }
    $sep = ',';
    $columns = array();
    foreach (array_merge($uniques, $sources) as $col) {
      if (strpos($col, $sep) !== FALSE) {
        $col = '"' . str_replace('"', '""', $col) . '"';
      }
      $columns[] = $col;
    }
    drupal_add_http_header('Cache-Control', 'max-age=60, must-revalidate');
    drupal_add_http_header('Content-Disposition', 'attachment; filename="' . $this->id . '_template.csv"');
    drupal_add_http_header('Content-type', 'text/csv; charset=utf-8');
    print implode($sep, $columns);
    return;
  }
}
