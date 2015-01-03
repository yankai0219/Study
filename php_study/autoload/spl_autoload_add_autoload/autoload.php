<?php
function __autoload($cls)
{
    $newcls = 'auto_' . $cls . '.php';
    include($newcls);
}
spl_autoload_register('__autoload');

