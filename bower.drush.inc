<?php
/**
 * @file
 * Bower drush command.
 */

/**
 * Implements hook_drush_command().
 */
function bower_drush_command() {
  $items = array();
  $items['bower-install'] = array(
    'description' => "Install bower dependencies into /libraries.",
    'arguments' => array(),
    'options' => array(),
    'examples' => array(),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function bower_drush_help($section) {
  switch ($section) {
    case 'drush:bower-install':
      return dt("This command will install/update all bower dependencies defined in any modules.");
  }
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_bower_install() {
  drush_print(dt('Installing bower dependencies...'));
  $flags = \FilesystemIterator::UNIX_PATHS;
  $flags |= \FilesystemIterator::SKIP_DOTS;
  $flags |= \FilesystemIterator::FOLLOW_SYMLINKS;
  $flags |= \FilesystemIterator::CURRENT_AS_SELF;

  $dir_prefix = 'modules/';
  $directory = new \RecursiveDirectoryIterator(DRUPAL_ROOT . '/' . $dir_prefix, $flags);
  $filter = new \RecursiveCallbackFilterIterator($directory, function ($current, $key, $iterator) {
    if ($current->isDir()) {
      return TRUE;
    }
    else {
      return strpos($current->getFilename(), 'bower.json') === 0;
    }
  });

  $iterator = new \RecursiveIteratorIterator($filter, \RecursiveIteratorIterator::LEAVES_ONLY,
    // Suppress filesystem errors in case a directory cannot be accessed.
    \RecursiveIteratorIterator::CATCH_GET_CHILD);
  $files = array();
  foreach ($iterator as $fileinfo) {
    $pathname = $dir_prefix . $fileinfo->getSubPathname();
    drush_log(dt('Installing !bower', array('!bower' => $pathname)), 'notice');

    $cwd_path = dirname($pathname);
    $num_dirs = substr_count($cwd_path, '/') + 1;
    $libraries_path = str_repeat('../', $num_dirs) . 'libraries';
    $command = 'bower install --config.directory=%s --allow-root';
    if (drush_shell_cd_and_exec($cwd_path, $command, $libraries_path)) {
      drush_log(dt('Successfully installed !bower.', array('!bower' => $pathname)), 'ok');
    }
    else {
      drush_log(dt('Failed to install !bower.', array('!bower' => $pathname)), 'error');
    }
  }
}
