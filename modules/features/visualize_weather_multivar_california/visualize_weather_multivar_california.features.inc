<?php
/**
 * @file
 * visualize_weather_multivar_california.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function visualize_weather_multivar_california_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function visualize_weather_multivar_california_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function visualize_weather_multivar_california_node_info() {
  $items = array(
    'data_weather_multi_california' => array(
      'name' => t('Data Weather Multi California'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
