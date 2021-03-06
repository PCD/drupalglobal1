<?php

/**
 * Admin Settings Page callback. Just renders a listing of currently active
 * node alternate locations.
 */
function nodesymlinks_admin() {
  $output = '<p>' . t('All alternate node locations') . '</p>';

  $result = db_query("SELECT * FROM {menu_links} WHERE module = :module AND link_path LIKE 'node/%%/mid/%%' ORDER BY link_path ASC", array(':module' => 'nodesymlinks'));
  $menus = menu_get_menus();

  // Render items
  $rows = array();
  while ($item = $result->fetch()) {
    $item->options = unserialize($item->options);
    $parent_options = menu_parent_options($menus, array('mlid' => 0));

    $row = array();
    $parent_option_id = $item->menu_name . ':' . $item->plid;
    $parent_name = isset($parent_options[$parent_option_id]) ? $parent_options[$parent_option_id] : '';
    $parent_menu_item = menu_link_load($item->plid);
    $link_parts = explode('/', $item->link_path);

    // Original node, Parent, Alternate location, Weight, Edit link
    $row[] = l($item->options['attributes']['title'], 'node/' . $link_parts[1]);
    $row[] = l($parent_name, $parent_menu_item['link_path']);
    $row[] = l($item->link_title, $item->link_path);
    $row[] = $item->weight;
    $row[] = l(t('Edit'), 'node/' . $link_parts[1] . '/edit');

    $rows[] = $row;
  }

  if (empty($rows)) {
    $output .= '<p>' . t('No node symlink found.') . '</p>';
  }
  else {
    $header = array(
      t('Original Node'),
      t('Parent Item'),
      t('Link title'),
      t('Weight'),
      t('Links')
    );
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }

  return $output;
}

/**
 * Admin settings form
 */
function nodesymlinks_settings($form, $form_state) {
  $form = array();

  $form['breadcrumbs'] = array(
    '#type' => 'fieldset',
    '#title' => 'Breadcrumb settings'
  );
  // TODO: Remove? Probably unnecessary in Drupal 7.
//  $form['breadcrumbs']['nodesymlinks_crumbs_include_home'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Breadcrumbs starts with "Home" link'),
//    '#default_value' => variable_get('nodesymlinks_crumbs_include_home', 1),
//  );
  $form['breadcrumbs']['nodesymlinks_crumbs_lastcrumb'] = array(
    '#type' => 'radios',
    '#title' => t('Last breadcrumb is'),
    '#options' => array(
      'parent' => t('Parent of the current menu item'),
      'current_plain' => t('Current menu item title'),
      'current_link' => t('Current menu item as link')
    ),
    '#default_value' => variable_get('nodesymlinks_crumbs_lastcrumb', 'parent'),
  );

  $form['nodeform'] = array(
    '#type' => 'fieldset',
    '#title' => 'Node form'
  );
  $form['nodeform']['nodesymlinks_check_menuitem'] = array(
    '#type' => 'checkbox',
    '#title' => t('Node menu item check'),
    '#description' => t('Check if the node menu item is filled when some node symlink is defined. When enabled it will' .
            ' warn you every time when you try to add nodesymlink leaving <b>Menu link title</b> field empty.'),
    '#default_value' => variable_get('nodesymlinks_check_menuitem', 1),
  );

  // TODO: Remove? Probably unnecessary in Drupal 7.
//  $form['pathauto'] = array(
//    '#type' => 'fieldset',
//    '#title' => 'Pathauto',
//    '#description' => t('These settings will be visible only when <a href="@url-project">@module</a> module is enabled on the <a href="@url-modules">Modules</a> page.', array('@module' => 'Pathauto', '@url-project' => 'http://drupal.org/project/pathauto', '@url-modules' => url('admin/modules'))),
//  );

//  if (module_exists('pathauto')) {
//    $form['pathauto']['nodesymlinks_node_tokens'] = array(
//      '#type' => 'checkbox',
//      '#title' => t('Use node tokens'),
//      '#default_value' => variable_get('nodesymlinks_node_tokens', 0),
//      '#description' => t('When enabled, it allows you to use the <em>node tokens</em> inside the <a href="@url-pattern">nodesymlinks pathauto pattern</a>. However it will consume slightly more resources. So enable this only when you really need it.', array('@url-pattern' => url('admin/config/search/path/patterns'))),
//    );
//  }

  return system_settings_form($form);
}
