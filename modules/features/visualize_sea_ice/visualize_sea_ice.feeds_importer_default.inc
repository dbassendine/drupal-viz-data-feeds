<?php
/**
 * @file
 * visualize_sea_ice.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function visualize_sea_ice_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_seaice';
  $feeds_importer->config = array(
    'name' => 'Sea Ice',
    'description' => 'Import Sea Ice extent data from NSIDC (http://nsidc.org/data/seaice_index/archives/)',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
        'header_size' => '1',
        'header_active' => '1',
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'data_seaice',
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'Year',
            'target' => 'guid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'Year',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Year',
            'target' => 'field_data_year:start',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Region',
            'target' => 'field_data_seaice_region',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Extent',
            'target' => 'field_data_seaice_extent',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Area',
            'target' => 'field_data_seaice_area',
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
  $export['import_seaice'] = $feeds_importer;

  return $export;
}
