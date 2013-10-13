<?php
/**
 * @file
 * visualize_sea_ice.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function visualize_sea_ice_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'vis_seaice';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Visualize Sea Ice';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Visualize Sea Ice';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'flot_fields';
  $handler->display->display_options['style_options']['size'] = '600x600';
  $handler->display->display_options['style_options']['legend'] = array(
    'noColumns' => '1',
    'labelBoxBorderColor' => '#ccc',
    'position' => 'bottom',
    'margin' => array(
      'x' => '5',
      'y' => '5',
    ),
    'backgroundColor' => '',
    'backgroundOpacity' => '0.85',
  );
  $handler->display->display_options['style_options']['yaxis'] = array(
    'label' => 'default',
    'position' => 'left',
    'color' => '',
    'tickColor' => '',
    'min' => '',
    'max' => '',
    'autoscaleMargin' => '0.02',
    'granularity' => 'auto',
    'labelWidth' => '',
    'labelHeight' => '',
  );
  /* Field: Content: Year (Date) */
  $handler->display->display_options['fields']['field_data_year']['id'] = 'field_data_year';
  $handler->display->display_options['fields']['field_data_year']['table'] = 'field_data_field_data_year';
  $handler->display->display_options['fields']['field_data_year']['field'] = 'field_data_year';
  $handler->display->display_options['fields']['field_data_year']['label'] = 'Year';
  $handler->display->display_options['fields']['field_data_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_year']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Extent */
  $handler->display->display_options['fields']['field_data_seaice_extent']['id'] = 'field_data_seaice_extent';
  $handler->display->display_options['fields']['field_data_seaice_extent']['table'] = 'field_data_field_data_seaice_extent';
  $handler->display->display_options['fields']['field_data_seaice_extent']['field'] = 'field_data_seaice_extent';
  $handler->display->display_options['fields']['field_data_seaice_extent']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_seaice_extent']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_data_seaice_extent']['flot'] = array(
    'axis' => 'y',
    'x' => array(
      'mode' => '',
    ),
    'y' => array(
      'type' => 'line',
      'color' => '',
      'function' => 'sum',
    ),
  );
  /* Field: Content: Area */
  $handler->display->display_options['fields']['field_data_seaice_area']['id'] = 'field_data_seaice_area';
  $handler->display->display_options['fields']['field_data_seaice_area']['table'] = 'field_data_field_data_seaice_area';
  $handler->display->display_options['fields']['field_data_seaice_area']['field'] = 'field_data_seaice_area';
  $handler->display->display_options['fields']['field_data_seaice_area']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_seaice_area']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_data_seaice_area']['flot'] = array(
    'axis' => 'y',
    'x' => array(
      'mode' => '',
    ),
    'y' => array(
      'type' => 'line',
      'color' => '',
      'function' => 'sum',
    ),
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'data_seaice' => 'data_seaice',
  );

  /* Display: Page: Flot fields */
  $handler = $view->new_display('page', 'Page: Flot fields', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'seaice-flotfields';

  /* Display: Page: Flot */
  $handler = $view->new_display('page', 'Page: Flot', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'flot';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Data point */
  $handler->display->display_options['fields']['datapoint']['id'] = 'datapoint';
  $handler->display->display_options['fields']['datapoint']['table'] = 'views';
  $handler->display->display_options['fields']['datapoint']['field'] = 'datapoint';
  $handler->display->display_options['fields']['datapoint']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['datapoint']['series'] = array(
    'field' => 'node.created',
    'grouping' => 'Y-m-d-H',
    'date_format' => 'short',
  );
  $handler->display->display_options['fields']['datapoint']['value'] = array(
    'field' => 'field_data_field_data_seaice_area.field_data_seaice_area',
    'format' => 'raw',
  );
  $handler->display->display_options['path'] = 'seaice-flot';
  $export['vis_seaice'] = $view;

  return $export;
}
