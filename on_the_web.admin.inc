<?php
/**
 * @file
 * Administrative interface for On The Web module.
 */

/**
 * Settings form.
 */
function on_the_web_settings_form($form, &$form_state) {
  $config = config('on_the_web.settings');
  $form = array();

  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Icon type'),
    '#options' => array(
      'font' => t('Icon font tags'),
      'anchor' => t('CSS background SVGs'),
      'image' => t('Image tags (legacy images)'),
    ),
    '#default_value' => $config->get('type'),
    'font' => array(
      '#description' => t('Various optios for Icon fonts will be provided below.'),
    ),
    'anchor' => array(
      '#description' => t('SVG icons will approximately match the icon fonts.'),
    ),
    'image' => array(
      '#description' => t('Note: Not all icons are available as images. This option will be rmeoved in a future version of this module.'),
    ),
  );
  $form['square'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use 'square' icons when available."),
    '#default_value' => $config->get('square'),
    '#states' => array(
      'invisible' => array(
        ':input[name="type"]' => array('value' => 'image'),
      ),
    ),
  );

  $sources = array(
    'forkawesome' => array(
      'key' => '1.2.0',
      'label' => 'ForkAwesome version 1.2.0',
      'icons_url' => 'http://forkaweso.me/Fork-Awesome/icons',
      'description' => t('The FontAwesome Fork'),
    ),
    'fontawesome_5' => array(
      'key' => '5.x.x',
      'label' => 'FontAwesome version 5.x (requires registration)',
      'icons_url' => 'https://fontawesome.com/v5.15/icons',
      'description' => t('The latest version of FontAwesome. <a href=":faurl">FontAwesome account</a> Required.', array(':faurl' => 'https://fontawesome.com/start')),
    ),
    'fontawesome' => array(
      'key' => '4.7.0',
      'label' => 'FontAwesome version 4.7.0',
      'icons_url' => 'https://fontawesome.com/v4.7/icons',
      'description' => t('The last Open Source version of FontAwesome'),
    ),
  );
  
  $form['version'] = array(
    '#type' => 'radios',
    '#title' => t('Icon Font and Version'),
    '#default_value' => $config->get('version'),
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array('value' => 'font'),
      ),
    ),
  );

  $source_options = array();
  foreach ($sources as $source) {
    $icons_link = l('see icons', $source['icons_url']);
    $source_options[$source['key']] = $source['label'] . ' &mdash; ' . $icons_link;
    $form['version']['key']['#description'] = $source['description'];
  }

  $form['version']['#options'] = $source_options;

  $form['kit_hash'] = array(
    '#type' => 'textfield',
    '#title' => t('FontAwesome 5.x Kit Hash'),
    '#field_prefix' => 'https://kit.fontawesome.com/',
    '#field_suffix' => '.js',
    '#size' => 20,
    '#default_value' => $config->get('kit_hash'),
    '#attributes' => array(
      'placeholder' => 'abcdefghij',
    ),
    '#description' => t('A 10-digit hash from the FontAwesome Kit code. <a href=":faurl">Register with FontAwesome</a> to generate a Kit.', array(':faurl' => '')),
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array('value' => 'font'),
        ':input[name="version"]' => array('value' => '5.x.x'),
      ),
    ),
  );

  $form['size'] = array(
    '#type' => 'radios',
    '#title' => t('Icon size'),
    '#options' => array(
      'sm' => t('Small: ~32px square'),
      'lg' => t('Large: ~64px square'),
    ),
    '#default_value' => $config->get('size'),
  );
  $form['sitename'] = array(
    '#type' => 'radios',
    '#title' => 'Hover text selection',
    '#default_value' => (int)$config->get('sitename'),
    '#description' => t('This setting will update the title attribute for each social media link.'),
    '#options' => array(
      1 => t('Use the <strong><a href="!url">Site name</a></strong>, for example: <em>Find !us on Facebook</em>', array('!us' => config_get('system.core', 'site_name'), '!url' => url('admin/config/system/site-information'))),
      0 => t('Use <strong>us</strong>, for example: <em>Find us on Facebook</em>'),
      2 => t('Use <strong>me</strong>, for example: <em>Find me on Facebook</em>'),
    ),
  );
  $form['target'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open links in new windows'),
    '#default_value' => $config->get('target'),
    '#description' => t('Unchecking this box his will remove the target="_blank" attribute from each link.'),
  );

  // Get all the services.
  $services = on_the_web_get_services();

  foreach ($services as $service => $info) {
    $weight = $config->get($service . '_weight');

    $form['services'][$service] = array(
      '#tree' => TRUE,
      '#weight' => $weight,
    );

    $form['services'][$service]['name'] = array('#hidden' => $service);

    $form['services'][$service]['title'] = array('#markup' => $info['name']);

    $form['services'][$service]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $weight,
    );

    $form['services'][$service]['page'] = array(
      '#type' => 'textfield',
      '#default_value' => $config->get($service . '_page'),
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'));

  return $form;
}

/**
 * Submit handler for on_the_web_settings_form().
 */
function on_the_web_settings_form_submit($form, &$form_state) {
  $services = on_the_web_get_services();

  $config = config('on_the_web.settings');
  $config->set('type', $form_state['values']['type']);
  $config->set('square', $form_state['values']['square']);
  $config->set('version', $form_state['values']['version']);
  $config->set('kit_hash', $form_state['values']['kit_hash']);
  $config->set('size', $form_state['values']['size']);
  $config->set('sitename', $form_state['values']['sitename']);
  $config->set('target', $form_state['values']['target']);

  foreach ($services as $name => $info) {
    $config->set($name . '_page', $form_state['values'][$name]['page']);
    $config->set($name . '_weight', $form_state['values'][$name]['weight']);
  }

  $config->save();
}
