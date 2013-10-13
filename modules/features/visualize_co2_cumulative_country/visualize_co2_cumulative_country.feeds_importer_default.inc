<?php
/**
 * @file
 * visualize_co2_cumulative_country.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function visualize_co2_cumulative_country_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_co2_cumulative_by_country';
  $feeds_importer->config = array(
    'name' => 'Cumulative CO2 by Country',
    'description' => 'Import from Fusion table http://goo.gl/Uxava',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
        'header_size' => 1,
        'header_active' => 1,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'data_co2_cumulative_by_country',
        'expire' => '-1',
        'author' => 0,
        'authorize' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'rowid',
            'target' => 'field_rowid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'rowid',
            'target' => 'guid',
            'unique' => 1,
          ),
          2 => array(
            'source' => 'Country',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Country',
            'target' => 'field_country',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'CO2',
            'target' => 'field_co2_cumulative',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_co2_cumulative_by_country'] = $feeds_importer;

  return $export;
}
