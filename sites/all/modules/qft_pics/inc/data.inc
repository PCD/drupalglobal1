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
 * lugar => A field lugar term id.
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
  
  // Taxonomy
  if ( isset($params['lugar']) ) {
    $node->field_lugar[$node->language][0]['tid'] = $params['lugar'];
  }
  
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

/**
 * Creates a galeria out of a post.
 */
function qft_pics_create_gallery_from_post($params) {
  // Save and get file.
  try{
    $file = qft_pics_save_file_from_gallery_post();
  } catch (Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
    return false;
  }
  
  // Create node
  $node = new stdClass();
  $node->type = 'galeria';
  $node->status = 1;
  node_object_prepare($node);
  
  // User fields
  $node->title = $params['title'];
  $node->language = LANGUAGE_NONE;
  $node->uid = 1;
  
  // GENERAL
  $node->body[$node->language][0]['value'] = $params['body'];
  $node->body[$node->language][0]['format'] = 'filtered_html';
  $node->created = strtotime("{$params['date']['year']}/{$params['date']['month']}/{$params['date']['day']}");
  $node->field_lugar[$node->language][0]['tid'] = $params['place'];
  
  // Attach File
  $file->display = 1;
  $file->description = '';
  $file->rdf_mapping = array();
  $node->field_zipped_files[$node->language][0] = (array) $file;
  
  // Unzip it and Attach Images.
  qft_pics_create_gallery_from_post_process_zipped_files($node);
  
  // Save
  try{
    $node = node_submit($node);
    node_save($node);
  } catch (Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
    return false;
  }
  
  return $node;
}

/**
 * Saves a file out of the post for creating a gallery.
 */
function qft_pics_save_file_from_gallery_post() {
  $handle = fopen($_FILES['files']['tmp_name']['pictures_zip'], 'r');
  $name = $_FILES['files']['name']['pictures_zip'];
  $file = file_save_data($handle, "public://{$name}");
  fclose($handle);
  return $file;
}

/**
 * Process Zipped Files.
 */
function qft_pics_create_gallery_from_post_process_zipped_files(&$node) {
  if ( !isset($node->field_zipped_files[$node->language][0]['uri']) ) {
    return false;
  }
  $zipped_files_path = drupal_realpath($node->field_zipped_files[$node->language][0]['uri']);
  
  // Start unziping
  $zip = new ZipArchive();
  $resource = $zip->open($zipped_files_path);
  if ( !($resource === TRUE) ) {
    return false;
  }
  
  
  // Copy the file.
  $temp = file_directory_temp();
  $time = time();
  $files_to_attach = array();
  for($i = 0; $i < $zip->numFiles; $i++) {
    $entry = $zip->getNameIndex($i);
    if ( preg_match('#\.(jpg)$#i', $entry) ) {
      //$entry_path = "{$zipped_files_path}#{$entry}";
      $temp_path = "{$temp}/";
      if ( $zip->extractTo($temp_path, array($entry)) ) {
        $files_to_attach[] = array(
          'name' => $entry, 
          'path' => "{$temp}/{$entry}", 
        );
      }
    }
  }
  $zip->close();
  
  // Attach Copied Files
  foreach($files_to_attach as $i => $file_to_attach) {
    $handle = fopen($file_to_attach['path'], 'r');
    $file = file_save_data($handle, "public://{$file_to_attach['name']}");
    fclose($handle);
    $file->display = 1;
    $file->description = '';
    $file->rdf_mapping = array();
    $node->field_images[$node->language][$i] = (array) $file;
  }
  return true;
}