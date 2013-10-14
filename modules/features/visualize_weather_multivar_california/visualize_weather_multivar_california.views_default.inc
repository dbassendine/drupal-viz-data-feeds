<?php
/**
 * @file
 * visualize_weather_multivar_california.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function visualize_weather_multivar_california_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'vis_weather_multi_california';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Visualize Weather Multivariable by Station';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CO2 (Google Scatter)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_station' => 'field_station',
    'field_temp_avgmax' => 'field_temp_avgmax',
    'field_temp_avgmin' => 'field_temp_avgmin',
    'field_precip_avgtotal' => 'field_precip_avgtotal',
    'field_date' => 'field_date',
  );
  $handler->display->display_options['style_options']['default'] = 'field_station';
  $handler->display->display_options['style_options']['info'] = array(
    'field_station' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_temp_avgmax' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_temp_avgmin' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_precip_avgtotal' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['label'] = 'Source';
  $handler->display->display_options['footer']['area']['content'] = 'Source (original): http://www.wrcc.dri.edu (via http://www.mkgeomatics.com/wordpress/?p=247)
Source (fusion table): http://goo.gl/O7yEQ
';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  /* Field: Content: Station */
  $handler->display->display_options['fields']['field_station']['id'] = 'field_station';
  $handler->display->display_options['fields']['field_station']['table'] = 'field_data_field_station';
  $handler->display->display_options['fields']['field_station']['field'] = 'field_station';
  /* Field: Content: AvgMaxTemp */
  $handler->display->display_options['fields']['field_temp_avgmax']['id'] = 'field_temp_avgmax';
  $handler->display->display_options['fields']['field_temp_avgmax']['table'] = 'field_data_field_temp_avgmax';
  $handler->display->display_options['fields']['field_temp_avgmax']['field'] = 'field_temp_avgmax';
  $handler->display->display_options['fields']['field_temp_avgmax']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: AvgMinTemp */
  $handler->display->display_options['fields']['field_temp_avgmin']['id'] = 'field_temp_avgmin';
  $handler->display->display_options['fields']['field_temp_avgmin']['table'] = 'field_data_field_temp_avgmin';
  $handler->display->display_options['fields']['field_temp_avgmin']['field'] = 'field_temp_avgmin';
  $handler->display->display_options['fields']['field_temp_avgmin']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: AvgTotalPrecip */
  $handler->display->display_options['fields']['field_precip_avgtotal']['id'] = 'field_precip_avgtotal';
  $handler->display->display_options['fields']['field_precip_avgtotal']['table'] = 'field_data_field_precip_avgtotal';
  $handler->display->display_options['fields']['field_precip_avgtotal']['field'] = 'field_precip_avgtotal';
  $handler->display->display_options['fields']['field_precip_avgtotal']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'data_weather_multi_california' => 'data_weather_multi_california',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page: Highchart */
  $handler = $view->new_display('page', 'Page: Highchart', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Weather Multivariable 2009 (Highcharts)';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'highcharts';
  $handler->display->display_options['style_options']['format']['chart_type'] = 'line';
  $handler->display->display_options['style_options']['format']['title'] = 'Atmospheric CO2';
  $handler->display->display_options['style_options']['format']['swap_axes'] = 0;
  $handler->display->display_options['style_options']['y_axis']['title'] = 'CO2 (ppm)';
  $handler->display->display_options['style_options']['y_axis']['reversed'] = 0;
  $handler->display->display_options['style_options']['x_axis']['dataset_data'] = array(
    'field_co2' => 'field_co2',
    'field_year' => 0,
  );
  $handler->display->display_options['style_options']['x_axis']['dataset_label'] = 'field_year';
  $handler->display->display_options['style_options']['x_axis']['reversed'] = 0;
  $handler->display->display_options['style_options']['pie']['dataset_data'] = array(
    'field_co2' => 'field_co2',
    'field_year' => 0,
  );
  $handler->display->display_options['style_options']['pie']['selected_slice'] = 'field_co2';
  $handler->display->display_options['style_options']['pie']['donut_hole'] = '0';
  $handler->display->display_options['style_options']['pie']['data_labels'] = 1;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'weather/highchart';

  /* Display: Page: Flot */
  $handler = $view->new_display('page', 'Page: Flot', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Weather Multivariable 2009 (Flot)';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'flot_fields';
  $handler->display->display_options['style_options']['size'] = '600x600';
  $handler->display->display_options['style_options']['shadowSize'] = '4';
  $handler->display->display_options['style_options']['legend'] = array(
    'noColumns' => '2',
    'labelBoxBorderColor' => '#ccc',
    'position' => 'bottom',
    'margin' => array(
      'x' => '5',
      'y' => '5',
    ),
    'backgroundColor' => '',
    'backgroundOpacity' => '0.85',
  );
  $handler->display->display_options['style_options']['xaxis'] = array(
    'position' => 'bottom',
    'color' => '#666',
    'tickColor' => '',
    'min' => '',
    'max' => '',
    'autoscaleMargin' => '',
    'granularity' => 'auto',
    'labelWidth' => '',
    'labelHeight' => '',
  );
  $handler->display->display_options['style_options']['yaxis'] = array(
    'label' => 'default',
    'position' => 'left',
    'color' => '#666',
    'tickColor' => '',
    'min' => '300',
    'max' => '450',
    'autoscaleMargin' => '0.02',
    'granularity' => 'auto',
    'labelWidth' => '',
    'labelHeight' => '',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: CO2 */
  $handler->display->display_options['fields']['field_co2']['id'] = 'field_co2';
  $handler->display->display_options['fields']['field_co2']['table'] = 'field_data_field_co2';
  $handler->display->display_options['fields']['field_co2']['field'] = 'field_co2';
  $handler->display->display_options['fields']['field_co2']['label'] = 'CO2 (ppm)';
  $handler->display->display_options['fields']['field_co2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_co2']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_co2']['flot'] = array(
    'axis' => 'y',
    'x' => array(
      'mode' => '',
    ),
    'y' => array(
      'type' => 'line',
      'color' => 'blue',
      'function' => 'sum',
    ),
  );
  /* Field: Content: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_year']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['path'] = 'weather/flot';

  /* Display: Page: GVS Motion */
  $handler = $view->new_display('page', 'Page: GVS Motion', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Weather Multivariable 2009 (Google Column)';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'gvs';
  $handler->display->display_options['style_options']['title'] = '';
  $handler->display->display_options['style_options']['type'] = '9';
  $handler->display->display_options['style_options']['width'] = '750';
  $handler->display->display_options['style_options']['height'] = '350';
  $handler->display->display_options['style_options']['chartAreaL'] = '100';
  $handler->display->display_options['style_options']['chartAreaT'] = '50';
  $handler->display->display_options['style_options']['emlink'] = 1;
  $handler->display->display_options['style_options']['emlinkforever'] = 1;
  $handler->display->display_options['style_options']['isimage'] = 0;
  $handler->display->display_options['style_options']['xaxis'] = 'field_station';
  $handler->display->display_options['style_options']['yaxis1_1'] = 'field_date';
  $handler->display->display_options['style_options']['yaxis2'] = 'field_temp_avgmin';
  $handler->display->display_options['style_options']['yaxis3'] = 'field_temp_avgmax';
  $handler->display->display_options['style_options']['yaxis4'] = 'field_precip_avgtotal';
  $handler->display->display_options['style_options']['curveType'] = 'none';
  $handler->display->display_options['style_options']['is3D'] = 0;
  $handler->display->display_options['style_options']['isStacked'] = 0;
  $handler->display->display_options['style_options']['pieSliceText'] = 'percentage';
  $handler->display->display_options['style_options']['interpolateNulls'] = 0;
  $handler->display->display_options['style_options']['legend'] = 'none';
  $handler->display->display_options['style_options']['HaxisTitlePosition'] = 'out';
  $handler->display->display_options['style_options']['HaxisTextPosition'] = 'out';
  $handler->display->display_options['style_options']['HaxisNumberFormat'] = '0';
  $handler->display->display_options['style_options']['VaxisTitlePosition'] = 'out';
  $handler->display->display_options['style_options']['VaxisTextPosition'] = 'out';
  $handler->display->display_options['style_options']['VaxisNumberFormat'] = '0';
  $handler->display->display_options['style_options']['axisFontSizeX'] = '12';
  $handler->display->display_options['style_options']['axisFontSizeY'] = '12';
  $handler->display->display_options['style_options']['titleY'] = 'CO2 emissions (millions of metric tons)';
  $handler->display->display_options['style_options']['showChartButtons'] = 0;
  $handler->display->display_options['style_options']['showHeadermc'] = 0;
  $handler->display->display_options['style_options']['showSelectListComponent'] = 0;
  $handler->display->display_options['style_options']['showSidePanel'] = 0;
  $handler->display->display_options['style_options']['showXMetricPicker'] = 0;
  $handler->display->display_options['style_options']['showYMetricPicker'] = 0;
  $handler->display->display_options['style_options']['showXScalePicker'] = 0;
  $handler->display->display_options['style_options']['showYScalePicker'] = 0;
  $handler->display->display_options['style_options']['showAdvancedPanel'] = 0;
  $handler->display->display_options['style_options']['enableScrollWheel'] = 0;
  $handler->display->display_options['style_options']['showTipMap'] = 0;
  $handler->display->display_options['style_options']['showLineMap'] = 0;
  $handler->display->display_options['style_options']['displayAnnotations'] = 0;
  $handler->display->display_options['style_options']['displayAnnotationsFilter'] = 0;
  $handler->display->display_options['style_options']['allowHtml'] = 0;
  $handler->display->display_options['style_options']['displayDateBarSeparator'] = 0;
  $handler->display->display_options['style_options']['displayExactValues'] = 0;
  $handler->display->display_options['style_options']['displayLegendDots'] = 0;
  $handler->display->display_options['style_options']['displayRangeSelector'] = 0;
  $handler->display->display_options['style_options']['displayZoomButtons'] = 0;
  $handler->display->display_options['style_options']['pageSize'] = '10';
  $handler->display->display_options['style_options']['showRowNumber'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'weather/gvs/motion';

  /* Display: Admin */
  $handler = $view->new_display('page', 'Admin', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Weather station Min/Max Temperature and Precipitation (View table)';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'weather/table';
  $export['vis_weather_multi_california'] = $view;

  return $export;
}
