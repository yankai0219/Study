<?php
function __autoload($cls)
{
    echo __METHOD__ . "\n";
    $clsFileName = $cls . '.php';
    if (file_exists($clsFileName))
    {
        include($clsFileName);
    }
}

function __autoloadFunc($cls)
{
    echo __METHOD__ . "\n";
    if (strpos($cls, 'Auto') === 0)
    {
        $subcls = substr($cls, strlen('Auto'));
        $clsFileName = 'auto_' . strtolower($subcls) . '.php';
        if (file_exists($clsFileName))
        {
            include($clsFileName);
        }
    }
}

function __autoloadTestFunc($cls)
{
    echo __METHOD__ . "\n";
    if (strpos($cls, 'Test') === 0)
    {
        $subcls = substr($cls, strlen('Test'));
        $clsFileName = 'test_' . strtolower($subcls) . '.php';
        if (file_exists($clsFileName))
        {
            include($clsFileName);
        }
    }
}
# part1
if (function_exists('__autoload'))
{
    spl_autoload_register('__autoload');
}
# part2
spl_autoload_register('__autoloadFunc');
# part3
spl_autoload_register('__autoloadTestFunc');
