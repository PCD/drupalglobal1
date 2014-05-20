<?php
/**
 * Implements hook_permission.
 */
function asiganacustom_permission() {
  $candidatos = taxonomy_get_tree(2);
  $permissions = array();
  foreach($candidatos as $term) {
    $permissions["post-gallery-candidato-{$term->tid}"] = array(
      'title' => 'Subir Galerias al Candidato ' . $term->name, 
      'description' => 'Subir Galerias al Candidato ' . $term->name, 
    );
  }
  return $permissions;
}