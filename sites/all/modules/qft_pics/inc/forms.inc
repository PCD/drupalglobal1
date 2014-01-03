<?php
/**
 * Returns a drupal form that imports an external galery into a story node.
 */
function qft_pics_import_external_form(&$form_state) {
  $form = array();
  $form['url'] = array(
    '#type' => 'textfield', 
    '#title' => t('URL of the External Gallery'), 
    '#required' => true, 
  );
  $form['actions'] = array(
    '#type' => 'actions', 
    'submit' => array(
      '#type' => 'submit', 
      '#value' => t('Import'), 
      '#weight' => 1, 
    ), 
  );
  return $form;
}