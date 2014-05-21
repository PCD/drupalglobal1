<?php
/**
 * Implements hook_permission.
 */
function asiganacustom_permission() {
  $permissions = array(
    'post-gallery-to-all-candidatos' => array(
      'title' => 'Subir Galerias a cualquier Candidato', 
      'description' => 'Subir Galerias a cualquier Candidato', 
    ), 
  );
  /*
  $candidatos = taxonomy_get_tree(2);
  foreach($candidatos as $term) {
    $permissions["post-gallery-candidato-{$term->tid}"] = array(
      'title' => 'Subir Galerias al Candidato ' . $term->name, 
      'description' => 'Subir Galerias al Candidato ' . $term->name, 
    );
  }
  */
  return $permissions;
}