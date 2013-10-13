<?php
/**
 * @file
 * visualize_co2.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function visualize_co2_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function visualize_co2_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function visualize_co2_node_info() {
  $items = array(
    'data_co2' => array(
      'name' => t('Data CO2'),
      'base' => 'node_content',
      'description' => t('A CO2 Data point'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
