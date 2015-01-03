<?php

/**
 *  http://dissectionbydavid.wordpress.com/2010/11/03/php-spl-autoload-vs-__autoload/
 *  Takes class_with_underscores (or not) and converts underscores to
 *    folder names.  Then attempts to include_once the class.  Returns TRUE
 *    on success, E_USER_WARNING and FALSE if it cannot load the class
 *
 *  Example: data_db_login  ==  ./classes/data/db/login.php
 *
 *  Usage:
 *    include ('./autoloader.php')    // or whatever you want to call this file
 *    spl_autoload_register('class_autoloader');
 *
 *
 * @param string $class Class name with underscores representing directories
 * @return bool Returns TRUE upon success, E_USER_WARNING and FALSE upon failure
 */
function class_autoloader($class) {
    $folderedClass = str_replace('_', '/', $class);

    $curPath = dirname(__FILE__);
    $theClass = $curPath . '/classes/' . $folderedClass . '.php';

    if (file_exists($theClass) && include_once($theClass)) {
        return TRUE;
    } else {
        trigger_error("The class '$class' or the file '$theClass' failed to spl_autoload  ", E_USER_WARNING);
        return FALSE;
    }
}
// if __autoload is active, put it on the spl_autoload stack
if (is_array(spl_autoload_functions()) && in_array('__autoload', spl_autoload_functions())) {
    spl_autoload_register('__autoload');
}
spl_autoload_register('class_autoloader');
