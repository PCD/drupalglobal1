<?php
/**
 * Gets an array of all the image styles used to export the pics.
 */
function qft_pics_image_styles() {
  return array(
    'thumbnail' => 'thumbnail', 
    'medium' => 'medium', 
    'large' => 'large', 
    'evento_teaser' => 'evento-teaser', 
    'slider_home' => 'slider_home', 
  );
}

/**
 * Creates an event out of an import.
 * @param ARRAY $params An array with the following index values.
 * uid => user id of the User contacting the doctor.
 * pics => An array of arrays of grouped pictures.
 * description => The message body.
 * status => The status of the message.
 */
function qft_pics_import_event($params) {
  $node = new stdClass();
  $node->type = 'event';
  $node->status = $params['status'];
  node_object_prepare($node);
  
  // User fields
  $node->title = $params['title'];
  $node->language = LANGUAGE_NONE;
  $node->uid = $params['uid'];
  
  // GENERAL
  $node->body[$node->language][0]['value'] = $params['description'];
  $node->body[$node->language][0]['format'] = 'filtered_html';
  
  // Pictures
  foreach($params['pics'] as $group_id => $pics) {
    foreach($pics as $url) {
      $node->{$group_id}[$node->language][]['url'] = $url;
    }
  }
  
  try{
    $node = node_submit($node);
    node_save($node);
  } catch (Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
    return false;
  }

  return $node;
}