<?php
/**
 * Implements hook_node_insert.
 */
function asiganacustom_node_prepare($node) {
  if ( $node->type == 'galeria' && isset($node->field_candidato_tid) && !empty($node->field_candidato_tid)) {
    $node->field_candidato[LANGUAGE_NONE][0]['tid'] = $node->field_candidato_tid;
  }
}
