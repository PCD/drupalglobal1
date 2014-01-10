<?php
/**
 * Implements hook_menu.
 */
function qft_pics_menu() {
  $items = array();
  $items['node/%node/pics/%'] = array(
    'page callback' => 'qft_pics_menu_pics', 
    'page arguments' => array(1), 
    'access callback' => 'qft_pics_access_pics', 
    'access arguments' => array(1, 'Access Pics Remotely', 3), 
    'type' => MENU_CALLBACK, 
  );
  $items['admin/galeria/import'] = array(
    'page callback' => 'drupal_get_form', 
    'page arguments' => array('qft_pics_import_external_form'), 
    'access arguments' => array('Access Pics Remotely'), 
    'type' => MENU_CALLBACK, 
  );
  return $items;
}

/**
 * Returns a json export of all the pics of a gallery.
 */
function qft_pics_menu_pics($node) {
  $response = array(
    'title' => trim($node->title), 
    'description' => '', 
    'pics' => array(), 
  );
  if ( isset($node->body[$node->language][0]['safe_value']) ) {
    $response['description'] = trim($node->body[$node->language][0]['safe_value']);
  }
  $pics = array(
    'src' => array(), 
  );
  $styles = qft_pics_image_styles();
  foreach($node->field_images[$node->language] as $pic) {
    $pics['src'][] = file_create_url($pic['uri']);
    foreach($styles as $style_machine => $style) {
      $pics[$style_machine][] = image_style_url($style, $pic['uri']);
    }
  }
  $response['pics'] = $pics;
  header('Cache-Control: no-cache, must-revalidate');
  header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
  header('Content-type: application/json');
  print json_encode($response);
  exit;
}