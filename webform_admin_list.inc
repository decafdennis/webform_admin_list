<?php
// Developed by Dennis Stevense for Digital Deployment

/**
 * Menu callback for admin/content/webform.
 */
function webform_admin_list_page() {
  $webform_types = webform_variable_get('webform_node_types');
  $nodes = array();
  
  if (!empty($webform_types)) {
    $placeholders = db_placeholders($webform_types, 'varchar');
    $result = db_query(db_rewrite_sql("SELECT DISTINCT(n.nid), n.*, r.* FROM {node} n INNER JOIN {node_revisions} r ON n.vid = r.vid INNER JOIN {webform_component} w ON n.nid = w.nid WHERE n.type IN ($placeholders)", 'n', 'nid', $webform_types), $webform_types);
    
    while ($node = db_fetch_object($result)) {
      $nodes[] = $node;
    }
  }
  
  return theme('webform_admin_content', $nodes);
}
