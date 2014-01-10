<?php
/**
 * Returns a drupal form that imports an external galery into a story node.
 */
function qft_pics_import_external_form($form, &$form_state) {
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

/**
 * Process the submission of the form qft_pics_import_external_form.
 */
function qft_pics_import_external_form_submit($form, &$form_state) {
  $url = $form_state['values']['url'];
  $get = json_decode(qft_pics_curl_get($url));
  
  // Build $Params.
  global $user;
  $params = array(
    'title' => $get->title, 
    'uid' => $user->uid, 
    'status' => 1, 
    'description' => $get->description, 
    'pics' => array(), 
  );
  // Original
  if ( isset($get->pics->src) && !empty($get->pics->src) ) {
    foreach($get->pics->src as $pic) {
      $params['pics']['field_picture_src'][] = $pic;
    }
  }
  // Thumbnail
  if ( isset($get->pics->thumbnail) && !empty($get->pics->thumbnail) ) {
    foreach($get->pics->thumbnail as $pic) {
      $params['pics']['field_picture_thumbnail'][] = $pic;
    }
  }
  // Medium
  if ( isset($get->pics->medium) && !empty($get->pics->medium) ) {
    foreach($get->pics->medium as $pic) {
      $params['pics']['field_picture_medium'][] = $pic;
    }
  }
  // Large
  if ( isset($get->pics->large) && !empty($get->pics->large) ) {
    foreach($get->pics->large as $pic) {
      $params['pics']['field_picture_large'][] = $pic;
    }
  }
  // Evento Teaser
  if ( isset($get->pics->evento_teaser) && !empty($get->pics->evento_teaser) ) {
    foreach($get->pics->evento_teaser as $pic) {
      $params['pics']['field_picture_evento_teaser'][] = $pic;
    }
  }
  // Slider Home
  if ( isset($get->pics->slider_home) && !empty($get->pics->slider_home) ) {
    foreach($get->pics->slider_home as $pic) {
      $params['pics']['field_picture_slider_home'][] = $pic;
    }
  }

  if ( ($node = qft_pics_import_event($params)) ) {
    // Notify
    $link = l($node->title, 'node/' . $node->nid);
    $message = t('El evento !event_link ha sido importado exitosamente.', array('!event_link' => $link));
    drupal_set_message($message);
  }
}