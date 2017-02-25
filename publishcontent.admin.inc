<?php

/**
 * @file
 * Contains page callbacks for publishcontent
 */

/**
 * Administration settings form.
 */
function publishcontent_config_form($form, &$form_state) {
  $config = config('publishcontent.settings');
  $form['publishcontent_method'] = array(
    '#type' => 'radios',
    '#title' => t('Quick publish method'),
    '#default_value' => $config->get('publishcontent_method', PUBLISHCONTENT_METHOD_TABS),
    '#description' => t('Choose the quick links method. With no quick links, the published checkbox will still appear on the node edit form. Note that a Drupal cache clear occurs after changing this.'),
    '#options' => array(
      PUBLISHCONTENT_METHOD_NONE => t('None.'),
      PUBLISHCONTENT_METHOD_ACTION_LINKS => t('Action links on node view.'),
      PUBLISHCONTENT_METHOD_BUTTON => t('Button.'),
      PUBLISHCONTENT_METHOD_TABS => t('Tabs.'),
    ),
  );

  // Provide a central place to select which content types are supported.
  $node_types = node_type_get_names();
  $form['content_types_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Types'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('Choose the content types to support.'),
  );

  foreach ($node_types as $machine_name => $human_name) {
    $form['content_types_fieldset']['publishcontent_' . $machine_name] = array(
      '#type' => 'checkbox',
      '#title' => $human_name,
      '#default_value' => $config->get('publishcontent_' . $machine_name, FALSE),
    );
  }

  $form['#submit'][] = 'publishcontent_config_form_pre_submit';
  $form['#submit'][] = 'publishcontent_config_form_submit';
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save configuration'),
);
  $form['#submit'][] = 'publishcontent_config_form_post_submit';

  return $form;
}

/**
 * Form submission function.
 *
 * This retains a note about the current quick publish method.
 */
function publishcontent_config_form_pre_submit(&$form, &$form_submit) {
  drupal_static('publishcontent_config_form_mode', config_get('publishcontent.settings', 'publishcontent_method', PUBLISHCONTENT_METHOD_TABS));
}

/**
 * Form submission function.
 *
 */

function publishcontent_config_form_submit($form, &$form_state)
{
    $config = config('publishcontent.settings');
    foreach ($form_state['values'] as $key => $value) {
      $config->set($key, $value);
    }
    $config->save();
    backdrop_set_message(t('The configuration options have been saved.'));
}

/**
 * Form submission function.
 *
 * This runs after the quick publish form has been saved. If the quick publish
 * method changed then the site cache is flushed.
 */
function publishcontent_config_form_post_submit(&$form, &$form_submit) {
  $old_mode = &drupal_static('publishcontent_config_form_mode');

  // If the quick access mode changed then flush all caches.
  if ($old_mode != $form_submit['values']['publishcontent_method']) {
    drupal_flush_all_caches();
    drupal_set_message('All site caches have been cleared.');
  }
}
