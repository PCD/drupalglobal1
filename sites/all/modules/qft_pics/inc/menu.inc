<?php
/**
 * Implements hook_menu.
 */
function qft_pics_menu() {
  $items = array();
  $items['node/%node/pics'] = array(
    'page callback' => 'qft_pics_menu_pics', 
    'page arguments' => array(1), 
    'access callback' => 'qft_pics_access_pics', 
    'access arguments' => array(1, 'Access Pics Remotely'), 
    'type' => MENU_CALLBACK, 
  );
  
  $items['admin/gallery/import'] = array(
    'page callback' => 'drupal_get_form', 
    'page arguments' => array('qft_pics_import_external_form'), 
    'access arguments' => array('Access Pics Remotely'), 
    'type' => MENU_CALLBACK, 
  );
  $items['admin/gallery/new'] = array(
    'page callback' => 'drupal_get_form', 
    'page arguments' => array('qft_pics_create_remote_gallery'), 
    'access arguments' => array('Create A Remote Gallery'), 
    'type' => MENU_CALLBACK, 
  );
  $items['admin/gallery/new/post'] = array(
    'page callback' => 'qft_pics_menu_new_gallery_post', 
    'access arguments' => array('Post Pics Remotely'), 
    'type' => MENU_CALLBACK, 
  );
  $items['admin/config/media/qft_pics'] = array(
    'title' => 'Quien Falto Pictures',
    'description' => 'Adjust Quien Falto Pictures settings.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('qft_pics_admin_settings_form'),
    'access arguments' => array('administer site configuration'),
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

/**
 * Receives a pics post and process it.
 */
function qft_pics_menu_new_gallery_post() {
  // Validate Access
  if ( !isset($_POST['key']) ) {
    return false;
  }
  $access_key = variable_get('qft_pics-access_key', md5('qft_pics-access_key'));
  if ( $_POST['key'] != $access_key ) {
    return false;
  }
  
  // Save post
  print_r($_POST);
  exit;
}