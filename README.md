Bower Drush Commands
====================

Drush command which checks modules for `bower.json` files and installs their
dependencies into the `<drupal-root>/libraries` folder.

Usage
-----

    drush bower-install

Note: this does not resolve any conflicts between multiple bower.json files,
nor does it remove outdated dependencies.

Setup
-----

You can put the bower folder into any of the following places:

  1. A .drush folder in your HOME folder.
  2. Anywhere in a folder tree below an active module on your site.
  3. /usr/share/drush/commands (configurable)
  4. In an arbitrary folder specified with the --include option.
  5. Drupal's /drush or /sites/all/drush folders.
