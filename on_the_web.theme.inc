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
