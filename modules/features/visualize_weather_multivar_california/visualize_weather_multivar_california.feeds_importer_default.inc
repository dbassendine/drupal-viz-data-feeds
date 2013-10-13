<?php
/**
 * @file
 * visualize_weather_multivar_california.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function visualize_weather_multivar_california_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_weather_multi_california';
  $feeds_importer->config = array(
    'name' => 'Weather Multi California',
    'description' => 'From fusion table http://goo.gl/O7yEQ',
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
        'content_type' => 'data_weather_multi_california',
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
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
            'source' => 'Station',
            'target' => 'field_station',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Station',
            'target' => 'title',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Month',
            'target' => 'field_date:start',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'AvgMaxTemp',
            'target' => 'field_temp_avgmax',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'AvgMinTemp',
            'target' => 'field_temp_avgmin',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'AvgTotalPrecip',
            'target' => 'field_precip_avgtotal',
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
  $export['import_weather_multi_california'] = $feeds_importer;

  return $export;
}
