<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_secondary_form_opensearch_admin_settings_alter(&$form, &$form_state) {
  $facets = [];
  foreach (variable_get('ding_facetbrowser_facets', []) as $facet) {
    $facets[] = $facet['name'];
  }

  if (!in_array('facet.genreCategory', $facets)) {
    drupal_set_message(
      t(
        'Secondary search requires !facet. Please insert on !adminpage',
        [
          '!facet' => 'facet.genreCategory',
          '!adminpage' => l(
            t('Configure facets'),
            'admin/config/ting/facets'
          ),
        ]
      ),
      'warning'
    );
  }

  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting Subsearch');
  $form['subsearch_settings']['#description'] = t('Feature modules allow additional searches to be made based on predefined conditions.');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['secondary_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Secondary Ting Search settings'),
  ];

  $form['subsearch_settings']['secondary_settings']['trigger'] = [
    '#type' => 'fieldset',
    '#title' => t('Trigger'),
  ];

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_max'] = [
    '#type' => 'textfield',
    '#title' => t('Maximum number of results'),
    '#default_value' => variable_get('ting_subsearch_secondary_max', 100),
    '#description' => t('How many is maximum in order to trigger secondary search.'),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Challenge: Factor for calculating ratio between nonfiction and fiction'),
    '#default_value' => variable_get('ting_subsearch_secondary_factor', 2),
    '#description' => t('The condition is as following (nonfiction / factor) > fiction'),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_result_min'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum number of results for secondary search'),
    '#description' => t('Minimum of hits in order to trigger secondary search.'),
    '#default_value' => variable_get('ting_subsearch_secondary_result_min', 100),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_ps_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Ratio between primary and secondary searches'),
    '#default_value' => variable_get('ting_subsearch_secondary_ps_factor', 2),
    '#description' => t('Factor between amount of results from primary and secondary search.'),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_agency'] = [
    '#type' => 'textfield',
    '#title' => t('Secondary Agency'),
    '#default_value' => variable_get('ting_subsearch_secondary_agency', ''),
    '#description' => t('The agency for the secondary well configuration'),
  ];

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_profile'] = [
    '#type' => 'textfield',
    '#title' => t('Secondary Search profile'),
    '#default_value' => variable_get('ting_subsearch_secondary_profile', ''),
    '#description' => t('The Search profile for the secondary well configuration'),
  ];

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_search_link'] = [
    '#type' => 'textfield',
    '#title' => t('Secondary link'),
    '#description' => t('Could be something link https://bibliotek.dk/da/search/work?search_block_form=[keys] where [keys] are substituted with the search phrase.'),
    '#default_value' => variable_get('ting_subsearch_secondary_search_link', ''),
  ];

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_search_link_text'] = [
    '#type' => 'textfield',
    '#title' => t('Secondary link text'),
    '#default_value' => variable_get('ting_subsearch_secondary_search_link_text', ''),
    '#description' => t('Name of the secondary provider. Could be bibliotek.dk'),
  ];

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_number_of_results'] = [
    '#type' => 'textfield',
    '#title' => t('Number of results to show'),
    '#default_value' => variable_get('ting_subsearch_secondary_number_of_results', 4),
    '#description' => t('How many results should be shown from secondary well provider.'),
  ];
  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_position'] = [
    '#type' => 'radios',
    '#title' => t('Position of message'),
    '#options' => [
      'before' => t('Before'),
      'after' => t('After'),
    ],
    '#default_value' => variable_get('ting_subsearch_secondary_position', 'before'),
    '#description' => t('Should the message be positioned before or after the search result?'),
  ];
}
