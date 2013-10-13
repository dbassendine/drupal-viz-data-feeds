<?php
/**
 * @file
 * visualize_sea_ice.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function visualize_sea_ice_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function visualize_sea_ice_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function visualize_sea_ice_node_info() {
  $items = array(
    'data_seaice' => array(
      'name' => t('Data Sea Ice'),
      'base' => 'node_content',
      'description' => t('A sea ice extent data point (from http://nsidc.org/data/seaice_index/archives/, ftp://sidads.colorado.edu/DATASETS/NOAA/G02135/)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
