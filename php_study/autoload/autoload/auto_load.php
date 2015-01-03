<?php
function __autoload($cls)
{
    $curDir  = dirname(__FILE__);
    $clsPath = $curDir . '/' . strtolower($cls) . '.php';
    if (file_exists($clsPath))
    {
        include($clsPath);
    }
    else
    {
        throw new Exception($clsPath . ' file doesnot exist');
    }
}
