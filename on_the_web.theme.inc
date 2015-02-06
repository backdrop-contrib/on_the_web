<?php
/**
 * @file
 * All theme functions for On The Web.
 */

/**
 * Theme function
 *
 * @param $linked_image
 *    Linked icon.
 * @return 
 *    Linked image with wrapper markup.
 */
function theme_on_the_web_icon($variables){
  $linked_image = $variables['linked_image'];
  $classes = $variables['classes'] ? ' class="' . implode(' ', $variables['classes']) . '"' : '';

  if ($linked_image){
    $output = '<span' . $classes . '>' . $linked_image . '</span>';
    return $output;
  }
  return;
}

/**
 * Theme function
 *
 * @param $service
 *    Icon for appropriate service.
 * @param $link
 *    URL where link should point.
 * @param $title
 *    Title attribute for the link tag.
 *
 * @return
 *    Linked icon with wrapper markup.
 */
function theme_on_the_web_item($variables) {
  $service = $variables['service'];
  $link = $variables['link'];
  $title = $variables['title'];

  // Build the img tag.
  $image = theme('on_the_web_image', array('service' => $service, 'title' => $title));

  // Determine attributes for the link
  $attributes  = array(
    'title' => $title,
    'rel' => 'nofollow',
  );
  if (variable_get('on_the_web_target', TRUE) == TRUE) {
    $attributes['target'] = '_blank';
  }

  // Link the image and wrap it in a span.
  $linked_image = l($image, $link, array('attributes' => $attributes, 'html' => TRUE));

  return $linked_image;
}

/**
 * Theme function
 *
 * @param $service
 *    Icon for appropriate service.
 * @param $title
 *    Title attribute for the link tag.
 *
 * @return 
 *    Icon image of appropriate size.
 */
function theme_on_the_web_image($variables) {
  $service = $variables['service'];
  $title = $variables['title'];

  // Get the size.
  $size = variable_get('on_the_web_size', 'sm');

  // Assemble necessary variables for building the image.
  $variables = array(
    'path' => drupal_get_path('module', 'on_the_web') . '/images/' . $size . '/' . $service . '.png', 
    'alt' => $title,
    'title' => $title,
  );

  // Build the img tag.
  $image = theme('image', $variables);

  return $image;
}

/**
 * Theme the drag-and-drop form.
 *
 * Arranges records in a table, and adds the css and js for draggable sorting.
 *
 * @ingroup themeable
 * @ingroup forms
 */
function theme_on_the_web_settings_form($variables) {
  $form = $variables['form'];
  $rows = array();
  $disabled_rows = array();

  foreach (element_children($form['services'], TRUE) as $service) {
    $row = array();

    $row[] = drupal_render($form['services'][$service]['title']);
    $row[] = drupal_render($form['services'][$service]['page']);

    // Now, render the weight row.
    $form['services'][$service]['weight']['#attributes']['class'][] = 'icon-weight';
    $row[] = drupal_render($form['services'][$service]['weight']);

    // Add this row to our collection of rows, and give it the 'draggable' class.
    $rows[] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }

  $output = '';
  if (count($rows)) {
    $header = array(t('Icon'), t('URL'), t('Weight'));
    $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'on-the-web-settings-table')));
  }

  // Pull out the submit button.
  $submit = drupal_render($form['submit']);
  // Add the rest of the form elements on top.
  $output = drupal_render_children($form) . $output . $submit;

  drupal_add_tabledrag('on-the-web-settings-table', 'order', 'self', 'icon-weight');

  return $output;
}
