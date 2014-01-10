<?php
/**
 * Implements hook_permission.
 */
function qft_pics_permission() {
  return array(
    'Access Pics Remotely' => array(
      'title' => 'Access Pics Remotely', 
      'description' => 'Access Pics Remotely', 
    ), 
  );
}

/**
 * Gives or declined access to Node Pics export.
 */
function qft_pics_access_pics($node, $access, $key) {
  /*if ( $node->type != 'galeria' ) {
    return false;
  }*/
  
  if ( $node->status != 1 ) {
    return false;
  }
  
  if ( !user_access($access) ) {
    return false;
  }
  
  //e9c26c4fb01dce9959b96197ce7a853d
  $ikey = variable_get('qft_pics_access_key', 'qft_pics_access_key');
  $ikey = md5($ikey);
  if ( $key != $ikey ) {
    return false;
  }
  
  return true;
}