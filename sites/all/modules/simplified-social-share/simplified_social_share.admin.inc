<?php
/**
 * @file
 * Admin page callback file for the simplified_social_share module.
 */

/**
 * Implements Social Login setting for the socialsharing module.
 */
function simplified_social_share_admin_settings($form, &$form_state) { 
  drupal_add_js('http://code.jquery.com/ui/1.10.0/jquery-ui.js');
  drupal_add_js(drupal_get_path('module', 'simplified_social_share') . '/simplified_social_share.js');
  drupal_add_css(drupal_get_path('module', 'simplified_social_share') . '/simplified_social_share.admin.css');
  drupal_add_js('jQuery(document).ready(function() { 
    var horizontal_image="' . variable_get("socialsharing_horizontal_images") . '";
    var vertical_image="' . variable_get("socialsharing_vertical_images") . '";
    if(horizontal_image == 8 || horizontal_image == 9) {
      counter_horizntal_show();
    }
    else {
      sharing_horizonatl_show();
	  if(horizontal_image == 2 || horizontal_image == 3) {
        sharing_simplehorizonatl_show();
      } 
    }
    if(vertical_image == 6 || vertical_image == 7) {
      counter_vertical_show();
    }
    else {
      sharing_vertical_show();
    }
	var selected_theme = "' . variable_get("socialsharing_selected_share_interface") . '";
	if(selected_theme == "vertical"){
	  hidden_horizontal_widget();
	}
	else {
	  display_horizontal_widget();
	}
  });', array('type' => 'inline', 'scope' => 'header', 'weight' => 5));
  $my_path = drupal_get_path('module', 'simplified_social_share');
  global $base_url;
   $thanks_text = t('To activate the plugin, you will need to first configure it (manage your desired social networks, etc.) from your LoginRadius account. If you do not have an account, click <a href="@loginradius" target="_blank">here</a> and create one for FREE!<br/>We also offer Social Plugins for <a href="@joomla" target="_blank">Joomla</a>, <a href="@wordpress" target="_blank">Wordpress</a>, <a href="@vbulletin" target="_blank">vBulletin</a>, <a href="@vanillaforum" target="_blank">VanillaForum</a>, <a href="@magento" target="_blank">Magento</a>, <a href="@oscommerce" target="_blank">OSCommerce</a>, <a href="@prestashop" target="_blank">Prestashop</a>, <a href="@xcart" target="_blank">X-Cart</a>, <a href="@zencart" target="_blank">Zen-Cart</a>, <a href="@dotnetnuke" target="_blank">DotNetNuke</a> and  <a href="@blogengine" target="_blank">BlogEngine</a> <br/><a href="@loginradius" target="_blank"><br/><input class="form-submit" type="button" value="Set up my FREE account!"></a> (<a href="@get_sociallogin" target="_blank">How to set up an account?</a>)', array('@loginradius' => 'http://www.Loginradius.com/', '@joomla' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#joomlaextension', '@wordpress' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#wordpressplugin', '@vbulletin' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#vbulletinplugin', '@vanillaforum' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#vanillaaddons', '@magento' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#magentoextension', '@oscommerce' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#osCommerceaddons', '@prestashop' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#prestashopmodule', '@xcart' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#xcartextension', '@zencart' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#zencartplugin', '@dotnetnuke' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#dotnetnukemodule', '@blogengine' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms#blogengineextension', '@get_sociallogin' => 'http://support.loginradius.com/customer/portal/articles/593954'));
    $form['thanks_block'] = array(
     '#type' => 'fieldset',
    '#title' => t('Thank you for installing the LoginRadius Social Plugin!'),
    '#description' =>  $thanks_text,
  );
  $group = 'share';
  $form[$group] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Sharing SETTINGS'),
  );
  $form[$group]['socialsharing_enable_share'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable Social Sharing for your website?'),
    '#default_value' => variable_get('socialsharing_enable_share', 1),
    '#options' => array(
      1 => t('YES'),
      0 => t('NO'),
    )
  );
  $form[$group]['socialsharing_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#default_value' => variable_get('socialsharing_api_key', ''),
     '#description' => t('Insert LoginRadius API Key ( <a href="@get_socialloginandsocialshare" target="_blank">How to get it?</a> )', array('@get_socialloginandsocialshare' => 'http://support.loginradius.com/customer/portal/articles/677100-how-to-get-loginradius-api-key-and-secret')),
  );
  $form[$group]['socialsharing_horizontal'] = array(
    '#type' => 'item',
    '#prefix' => '<div><b>' . t('What Social Sharing widget theme do you want to use across your website?<div class="description">Horizontal and Vertical themes can be enabled simultaneously</div>') . '</b></div>',
    '#markup' => l(t('Horizontal'), "javascript:void(0)", array('fragment' => '', 'external' => TRUE, 'attributes' => array('id' => 'socialsharing_horizontal', 'onclick' => 'display_horizontal_widget();'))) . "<b>|</b>" . l(t('Vertical'), "javascript:void(0)", array('fragment' => '', 'external' => TRUE, 'attributes' => array('id' => 'socialsharing_veritical', 'onclick' => 'hidden_horizontal_widget();' )))
  );
  $form[$group]['socialsharing_selected_share_interface'] = array(
    '#type' => 'hidden',
    '#title' => t('selected share interface'),
    '#default_value' => variable_get('socialsharing_selected_share_interface'),
    '#suffix' => '<div id=lrsharing_divwhite></div><div id=lrsharing_divgrey></div><div id="show_horizontal_block">',
  );
   
   $form[$group]['socialsharing_enable_horizontal_share'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable Horizontal Social Sharing for your website?'),
    '#default_value' => variable_get('socialsharing_enable_horizontal_share', 1),
    '#options' => array(
      1 => t('YES'),
      0 => t('NO'),
    )
  );
   $form[$group]['socialsharing_enable_vertical_share'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable Vertical  Social Sharing for your website?'),
    '#default_value' => variable_get('socialsharing_enable_vertical_share', 1),
    '#options' => array(
      1 => t('YES'),
      0 => t('NO'),
    )
  );
 $form[$group]['socialsharing_label_string'] = array(
    '#type' => 'textfield',
    '#title' => t('What text do you want to display above the Social Sharing widget?'),
    '#default_value' => variable_get('socialsharing_label_string', 'Share it now!'),
    '#description' => t('Leave empty for no text.'),
  );
  $form[$group]['socialsharing_horizontal_images'] = array(
    '#type' => 'radios',
    '#id' => 'socialsharing_horizontal_images',
    '#default_value' => variable_get('socialsharing_horizontal_images', 0),
    '#options' => array(
       0 => '<img src="' . $base_url . '/' . $my_path . '/images/horizonSharing32.png"></img>',
       1 => '<img src="' . $base_url . '/' . $my_path . '/images/horizonSharing16.png"></img>',
       2 => '<img src="' . $base_url . '/' . $my_path . '/images/single-image-theme-large.png"></img>',
       3 => '<img src="' . $base_url . '/' . $my_path . '/images/single-image-theme-small.png"></img>',
       8 => '<img src="' . $base_url . '/' . $my_path . '/images/horizontalvertical.png"></img>',
       9 => '<img src="' . $base_url . '/' . $my_path . '/images/horizontal.png"></img>',
     ),
  );
  $form[$group]['socialsharing_vertical_images'] = array(
    '#type' => 'radios',
    '#id' => 'socialsharing_vertical_images',
    '#default_value' => variable_get('socialsharing_vertical_images', 6),
    '#options' => array(
       4 => '<img src="' . $base_url . '/' . $my_path . '/images/32VerticlewithBox.png"></img>',
       5 => '<img id="VerticlewithBox" src="' . $base_url . '/' . $my_path . '/images/16VerticlewithBox.png"></img>',
       6 => '<img src="' . $base_url . '/' . $my_path . '/images/hybrid-verticle-vertical.png"></img>',
       7 => '<img id="hybrid-verticle-horizontal"  src="' . $base_url . '/' . $my_path . '/images/hybrid-verticle-horizontal.png"></img>',
     ),
     '#attributes' => array('style' => 'display:inline'),
  );
  $form[$group]['socialsharing_show_horizotal']= array(
    '#type' => 'hidden',
    '#suffix' => '<div id="socialsharing_show_horizotal_widget">',
  );
   $counter_providers =variable_get('socialsharingcounter_rearrange_providers_list');
  if (empty($counter_providers)) {
    variable_set('socialsharingcounter_rearrange_providers_list', array( "0" => "Facebook Like", "1" => "Google+ +1", "2" => "Pinterest Pin it" , "3" => "LinkedIn Share", ));
  }
  $form[$group]['socialsharing_counter_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'socialcounter_show_providers_list',
    '#class' => 'form-item form-type-checkboxes form-item-socialshare-counter-show-providers-list',
    '#title' => t('What Sharing Networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
    '#default_value' => variable_get('socialsharingcounter_rearrange_providers_list'),
    '#suffix' => '<div id="socialcounter_hidden_field" style="display:none;">',
  );
  foreach (variable_get("socialsharingcounter_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $raw = $provider;
      $provider = str_replace(' ', '', $provider);
      $provider = str_replace("++", "plusplus", $provider);
      $provider = str_replace("+", "plus", $provider);
      $form[$group][$provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('lrshare_' . $provider)),
        '#markup' => '<input type = "hidden" id = "input-lrcounter-' . $provider . '" name = "socialsharingcounter_rearrange_providers_list[]" value = "' . $raw . '" />',
       );
    }
  }
  $share_providers =variable_get("socialsharing_rearrange_providers_list");
  if (empty($share_providers)) {
    variable_set('socialsharing_rearrange_providers_list', array( "0" => "facebook", "1" => "googleplus", "2" => "google", "3" => "pinterest", "4" => "twitter", ));
  }
  $form[$group]['socialsharing_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'socialsharing_providers_list',
    '#title' => t('What Sharing Networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
    '#default_value' => variable_get('socialsharing_rearrange_providers_list'),
    '#prefix' => '</div><div id="loginRadiusSharingLimit" style="color:red; display:none; margin-bottom: 5px;">' . t('You can select only 9 providers.') . '</div>',
    '#suffix' => '<div id="rearrange_sharing_text"><b>' . t('What sharing network order do you prefer for your sharing widget?(Drag around to set the order)') . '</b></div><ul id="socialsharing_rearrange_providers" class="socialsharing_rearrange_providers">',
  );
  foreach (variable_get("socialsharing_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $form[$group]['lrshare_iconsprite32' . $provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('lrshare_' . $provider)),
        '#markup' => '<li id = "edit-lrshare-iconsprite32' . $provider . '" class = "lrshare_iconsprite32 lrshare_' . $provider . '" title = "' . $provider . '" >
	    <input type = "hidden" id = "input-lrshare-' . $provider . '" name = "socialsharing_rearrange_providers_list[]" value = "' . $provider . '" /></li>', 
      );
    }
  }
  $form[$group]['socialsharing_rearran_providers_list']= array(
    '#type' => 'hidden',
    '#prefix' => '</ul><div id="socialsharing_question"></div>',
    '#suffix' => '</div>',
  ); 
   $form[$group]['socialsharing_show_veritical']= array(
    '#type' => 'hidden',
    '#suffix' => '<div id="socialsharing_show_veritcal_widget">',
  );
   $counter_providers =variable_get('socialsharingcounter_vertical_rearrange_providers_list');
  if (empty($counter_providers)) {
    variable_set('socialsharingcounter_vertical_rearrange_providers_list', array( "0" => "Facebook Like", "1" => "Google+ +1", "2" => "Pinterest Pin it" , "3" => "LinkedIn Share", ));
  }
  $form[$group]['socialsharing_counter_vertical_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'socialcounter_vertical_show_providers_list',
    '#title' => t('What Sharing Networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
    '#default_value' => variable_get('socialsharingcounter_vertical_rearrange_providers_list'),
    '#suffix' => '<div id="socialcounter_vertical_hidden_field" style="display:none;">',
  );
  foreach (variable_get("socialsharingcounter_vertical_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $raw = $provider;
      $provider = str_replace(' ', '', $provider);
      $provider = str_replace("++", "plusplus", $provider);
      $provider = str_replace("+", "plus", $provider);
      $form[$group]['lrshare_vertical_' . $provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('lrshare_vertical_' . $provider)),
        '#markup' => '<input type = "hidden" id = "input-lrcounter-vertical-' . $provider . '" name = "socialsharingcounter_vertical_rearrange_providers_list[]" value = "' . $raw . '" />',
      );
    }
  }
  $share_providers =variable_get("socialsharing_vertical_rearrange_providers_list");
  if (empty($share_providers)) {
    variable_set('socialsharing_vertical_rearrange_providers_list', array( "0" => "facebook", "1" => "googleplus", "2" => "google", "3" => "pinterest", "4" => "twitter", ));
  }
  $form[$group]['socialsharing_vetical_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'socialsharing_vetical_show_providers_list',
    '#title' => t('What Sharing Networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
    '#default_value' => variable_get('socialsharing_vertical_rearrange_providers_list'),
    '#prefix' => '</div><div id="loginRadiusSharingLimit_vertical" style="color:red; display:none; margin-bottom: 5px;">' . t('You can select only 9 providers.') . '</div>',
    '#suffix' => '<div id="rearrange_sharing_text_vertical"><b>' . t('What sharing network order do you prefer for your sharing widget?(Drag around to set the order)') . '</b></div><ul id="socialsharing_vertical_rearrange_providers" class="socialsharing_vertical_rearrange_providers">',
  );
  foreach (variable_get("socialsharing_vertical_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $form[$group]['lrshare_iconsprite32_vertical' . $provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('lrshare_' . $provider)),
        '#markup' => '<li id = "edit-lrshare-iconsprite32_vertical' . $provider . '" class = "lrshare_iconsprite32 lrshare_' . $provider . '" title = "' . $provider . '" >
	    <input type = "hidden" id = "input-lrshare-vertical-' . $provider . '" name = "socialsharing_vertical_rearrange_providers_list[]" value = "' . $provider . '" /></li>', 
      );
    }
  }
  $form[$group]['socialsharing_vertical_rearra_providers_list']= array(
    '#type' => 'hidden',
    '#prefix' => '</ul><div id="socialsharing_question"></div>',
    '#suffix' => '</div>',
  );
  $form[$group]['socialsharing_vertical_images']['socialsharing_vertical_position'] = array(
     '#type' => 'radios',
     '#title' => t('Select the position of Social Sharing widget'),
     '#weight' => 50,
     '#default_value' => variable_get('socialsharing_vertical_position', 0),
     '#options' => array(
        0 => t('Top Left'),
        1 => t('Top Right'),
        2 => t('Bottom Left'),
        3 => t('Bottom Right'),
      ),
  );
  $form[$group]['socialsharing_vertical_images']['socialsharing_vertical_position']['socialsharing_vertical_topweight'] = array(
    '#type' => 'textfield',
    '#title' => t('Specify distance of vertical sharing interface from top (Leave empty for default behaviour)'),
    '#weight' => 100,
    '#size' => 0,
    '#default_value' => variable_get('socialsharing_vertical_topweight'),
    '#description' => t('Enter a number (For example - 200). It will set the top CSS attribute of the interface to the value specified. Increase in the number pushes interface towards bottom.'),
  );
  $form[$group]['socialsharing_horizontal_location'] = array(
    '#title' => t('Location'),
    '#type' => 'radios',
    '#options' => array(
      'content' => t('Node content'),
      'block' => t('Block'),
      'links' => t('Links area'),
    ),
    '#default_value' => variable_get('socialsharing_horizontal_location', 'content'),
    '#description' => t('Select where the Social Share widget should appear. When selected to display as a block, you must choose which region to display the <em>Social Sharing block</em> in from the <a target="_blank" href="@blockssettings">Blocks Settings</a>.', array('@blockssettings' => url('admin/structure/block'))),
    '#attributes' => array('onclick' => 'display_block_horizontal(this.value);'),
  );
  $form[$group]['socialsharing_vertical_location'] = array(
    '#title' => t('Location'),
    '#type' => 'radios',
    '#options' => array(
      'content' => t('Node content'),
      'block' => t('Block'),
    ),
    '#default_value' => variable_get('socialsharing_vertical_location', 'content'),
    '#description' => t('Select where the Social Share widget should appear. When selected to display as a block, you must choose which region to display the <em>Social Share block</em> in from the <a target="_blank" href="@blockssettings">Blocks Settings</a>.', array('@blockssettings' => url('admin/structure/block'))),
    '#attributes' => array('onclick' => 'display_block_vertical(this.value);'),
  );
  $form[$group]['socialsharing_position_top'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show at the top of content.'),
    '#default_value' => variable_get('socialsharing_position_top', 1) ? 1 : 0,
    '#prefix' => '<div id="horizontal_sharing_show"> <b>Select the position of Social sharing interface</b>',
  );
   
  $form[$group]['socialsharing_position_bottom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show at the bottom of content.'),
    '#default_value' => variable_get('socialsharing_position_bottom', 1) ? 1 : 0,
    '#suffix' => '</div>',
  );
    $form[$group]['socialsharing_top_weight'] = array(
    '#title' => t('Select the Weight of Social Sharing widget at the top of content'),
    '#description' => t('The weight of the widget determines the location on the page where it will appear.'),
    '#required' => FALSE,
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(-100, -50, -25, -10, 0)),
    '#default_value' => variable_get('socialsharing_top_weight', -10),
  );
  $form[$group]['socialsharing_bottom_weight'] = array(
    '#title' => t('Select the Weight of Social Sharing widget at the bottom of content'),
    '#description' => t('The weight of the widget determines the location on the page where it will appear.'),
    '#required' => FALSE,
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(0, 10, 25, 50, 100)),
    '#default_value' => variable_get('socialsharing_bottom_weight', 10),
  );
  $form[$group]['socialsharing_show_pages'] = array(
    '#type' => 'radios',
    '#title' => t('Show Social Share on specific pages'),
    '#default_value' => variable_get('socialsharing_show_pages', 0),
    '#options' => array(
      0 => t('All pages except those listed'),
      1 => t('Only the listed pages'),
     ),
  );
  $form[$group]['socialsharing_show_exceptpages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('socialsharing_show_exceptpages', ''),
    '#description' => t('Enter a page title(you give on page creation) or node id (if url is http://example.com/node/1 then enter 1(node id)) with comma sepreted'),
    '#rows' => 5,
  );
    $form[$group]['socialsharing_vertical_show_pages'] = array(
    '#type' => 'radios',
    '#title' => t('Show Social Share on specific pages'),
    '#default_value' => variable_get('socialsharing_vertical_show_pages', 0),
    '#options' => array(
      0 => t('All pages except those listed'),
      1 => t('Only the listed pages'),
     ),
  );
  $form[$group]['socialsharing_vertical_show_exceptpages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('socialsharing_vertical_show_exceptpages', ''),
    '#description' => t('Enter a page title(you give on page creation) or node id (if url is http://example.com/node/1 then enter 1(node id)) with comma sepreted'),
    '#rows' => 5,
    '#suffix' => '</div>',
  );
  $form['#submit'][] = 'socialsharingbar_settings_submit';
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  
  return $form;
}


 /**
 * Submit the Social share settings.
 */
function socialsharingbar_settings_submit($form, &$form_state) {
   if (isset($form_state['input']['socialsharing_rearrange_providers_list'])) {
     variable_set('socialsharing_rearrange_providers_list', array_filter($form_state['input']['socialsharing_rearrange_providers_list']));
   } 
   else {
     variable_set('socialsharing_rearrange_providers_list', array( "0" => "facebook", "1" => "googleplus", "2" => "google", "3" => "pinterest", "4" => "twitter", ));
   }
   if (!empty($form_state['input']['socialsharingcounter_rearrange_providers_list'])) {
     variable_set('socialsharingcounter_rearrange_providers_list', array_filter($form_state['input']['socialsharingcounter_rearrange_providers_list']));
   } 
   else {
     variable_set('socialsharingcounter_rearrange_providers_list', array( "0" => "Facebook Like", "1" => "Google+ +1", "2" => "Pinterest Pin it" , "3" => "LinkedIn Share", ));
   }
    if (isset($form_state['input']['socialsharing_vertical_rearrange_providers_list'])) {
     variable_set('socialsharing_vertical_rearrange_providers_list', array_filter($form_state['input']['socialsharing_vertical_rearrange_providers_list']));
   } 
   else {
     variable_set('socialsharing_vertical_rearrange_providers_list', array( "0" => "facebook", "1" => "googleplus", "2" => "google", "3" => "pinterest", "4" => "twitter", ));
   }
    if (!empty($form_state['input']['socialsharingcounter_vertical_rearrange_providers_list'])) {
     variable_set('socialsharingcounter_vertical_rearrange_providers_list', array_filter($form_state['input']['socialsharingcounter_vertical_rearrange_providers_list']));
   } 
   else {
     variable_set('socialsharingcounter_vertical_rearrange_providers_list', array( "0" => "Facebook Like", "1" => "Google+ +1", "2" => "Pinterest Pin it", "3" => "LinkedIn Share", ));
   }
  form_state_values_clean($form_state);
  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }
  drupal_set_message(t('The configuration options have been saved.'));
  // Clear the cached pages and blocks.
  cache_clear_all();
  menu_rebuild();
}

 
 
 /**
 * Implements help tab  for the socialsharing module.
 */
function simplified_social_share_user_help() {
  drupal_add_css(drupal_get_path('module', 'simplified_social_share') . '/simplified_social_share.admin.css');
  $help_text = t('<b>Help & Documentations</b><br/><a href="@install" target="_blank">Plugin Installation, Configuration and Troubleshooting</a><br/><a href="@api" target="_blank">How to get LoginRadius API Key & Secret</a><br/><a href="@forum" target="_blank">Discussion Forum</a><br><a href="@about" target="_blank">About LoginRadius</a><br><a href="@product" target="_blank">LoginRadius Products</a><br><a href="@plugin" target="_blank">Social Plugins</a><br><a href="@sdk" target="_blank">Social SDKs</a>', array('@loginradius' => 'http://www.Loginradius.com/', '@install' => 'http://support.loginradius.com/customer/portal/articles/1237617-drupal-social-sharing-installation', '@api' => 'http://support.loginradius.com/customer/portal/articles/677100-how-to-get-loginradius-api-key-and-secret', '@forum' => 'http://community.loginradius.com/', '@about' => 'http://www.loginradius.com/loginradius/about', '@product' => 'http://www.loginradius.com/product/sociallogin', '@plugin' => 'https://www.loginradius.com/loginradius-for-developers/loginRadius-cms', '@sdk' => 'https://www.loginradius.com/loginradius-for-developers/loginradius-sdks'));
   $sociallogin_get_updates = t('<b>Get Updates</b><br/><br/>To receive updates on new features, releases, etc, please connect to one of our social media pages -<br/><br/><div><iframe rel="tooltip" scrolling="no" frameborder="0" allowtransparency="true" style="border: none; overflow: hidden; width: 46px;
height: 61px; margin-right:10px" src="//www.facebook.com/plugins/like.php?app_id=194112853990900&href=http%3A%2F%2Fwww.facebook.com%2Fpages%2FLoginRadius%2F119745918110130&send=false&layout=box_count&width=90&show_faces=false&action=like&colorscheme=light&font=arial&height=90" data-original-title="Like us on Facebook"></iframe></div>
');
  $support_text = t('<b>Support Us</b><br/><br/>If you liked our FREE open-source plugin, please send your feedback/testimonial to <a href="@feedback">feedback@loginradius.com</a>!' , array('@feedback' => 'mailto:feedback@loginradius.com'));
 $form['help_block'] = array(
    '#type' => 'item',
    '#markup' => '<div id=thanks_block>' . $help_text . '</div>',
 );
 $form['thanks_block'] = array(
   '#type' => 'item',
   '#markup' => '<div style=float:left; id=sociallogin_get_update>' . $sociallogin_get_updates . '</div>',
 );
 $form['support_block'] = array(
   '#type' => 'item',
   '#markup' => '<div style=margin-left:785px;margin-top:-56px; id=sociallogin_get_update>' . $support_text . '</div>',
  );
  return $form;
}