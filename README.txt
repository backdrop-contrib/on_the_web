On the web.
=============
This module provides a single block that can show social media icons that link
to your brand's content located elsewhere on the web such as Twitter, Facebook
and the like.


Installation
-------------
Install this module as usual as per
http://drupal.org/documentation/install/modules-themes/modules-7


Configuration
--------------
Links for your site can be added in the block's configuration at
  Admin > Configure > Web services > On The Web

The Social Media Icons block can be configured and placed ad
  Admin > Structure > Blocks.


Customization
-------------

If you would like to use plain anchor tags without image tags so that you can provide your own background images or style more easily with CSS, you will probably need to override theme_on_the_web_image(). Place the following code in the template.php file in your theme, and replace 'mytheme' with the name of your theme:

/**
 * Overrides theme_on_the_web_image().
 */
function mytheme_on_the_web_image($variables) {
  return $variables['service'];
}

If you would like to change the order in which the icons appear, you can implement hook_on_the_web_get_services_alter() in a custom module, and change the order of the items in the list that's returned.

/**
 * Alter the services returned by on_the_web_get_services().
 *
 * This alter function can be used to:
 * - Change the order of links in the list of services.
 * - Add additional services.
 *
 * @see on_the_web_get_services().
 */
function mymodule_on_the_web_get_services_alter(&$services) {
  // Pull out facebook.
  $face = $services['facebook'];
  // Remove facebook.
  unset($services['facebook']);
  // Put facebook at the begining.
  $services = array('facebook' => $face)+$services;

  // Add an additional service.
  $services['soundcloud'] = array('name' => 'SoundCloud');
}


Icon Set
---------
The complete Elegant Themes icon set can be downloaded here:
http://www.elegantthemes.com/blog/resources/free-social-media-icon-set
Created by Nicholas Roach, www.elegantthemes.com
These icons are dual licensed under the MIT and GPL 3.0.


Support
-------
Please use the issue queue to report bugs or request support:
https://drupal.org/project/issues/on_the_web
