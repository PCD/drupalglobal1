<?php
/**
 * Implements hook_menu_alter.
 */
function qft_pics_menu_alter(&$items) {
  $items['node/%node']['page callback'] = 'qft_pics_menu_galeria_page_view';
}

/**
 * Alters the Page View Render of the Node.
 */
function qft_pics_menu_galeria_page_view($node) {
  drupal_set_title($node->title);
  $uri = entity_uri('node', $node);
  // Set the node path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);
  
  // Default node_show
  if ( $node->type != 'event' ) {
    return node_show($node);
  }
  
  // Use theme
  $output = '';
  
  // Build Galeria
  drupal_add_js(drupal_get_path('module', 'qft_pics') . '/js/jquery.jcarousel.js');
  drupal_add_js(drupal_get_path('module', 'qft_pics') . '/js/node-gallery.js');
  if ( isset($node->field_picture_evento_teaser[$node->language]) && isset($node->field_picture_large[$node->language]) ) {
    $teasers = $node->field_picture_evento_teaser[$node->language];
    $bigs = $node->field_picture_large[$node->language];
    $output = "<div id=\"quienfalto-gallery\">\n<ul>\n";
    foreach($teasers as $key => $teaser) {
      $output .= "<img src=\"{$bigs[$key]['url']}\" /> \n";
      //$output .= "<li><a class=\"colorbox\" rel=\"galeria\" href=\"{$bigs[$key]['url']}\"><img src=\"{$teaser['url']}\" /></a>\n";
    }
    $output .= "</ul>\n</div>\n";
    drupal_add_js(drupal_get_path('module', 'colorbox') . '/js/colorbox.js');
  }
  
  return $output;
}