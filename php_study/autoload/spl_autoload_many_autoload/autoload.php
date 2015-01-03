<?php
function __autoload($cls)
{
    echo __METHOD__ . "\n";
    include($cls . '.php');
}
function __autoloadFunc($cls)
{
    echo __METHOD__ . "\n";
    if (strpos($cls, 'Auto') === 0)
    {
        $subcls = substr($cls, strlen('Auto'));
        $clsFileName = 'auto_' . strtolower($subcls) . '.php';
        include($clsFileName);
    }
}
function __autoloadTestFunc($cls)
{
    echo __METHOD__ . "\n";
    if (strpos($cls, 'Test') === 0)
    {
        $subcls = substr($cls, strlen('Test'));
        $clsFileName = 'test_' . strtolower($subcls) . '.php';
        include($clsFileName);
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

/**
 * 说明：如果part1 before part2
 * 出现warning，提示找不到AutoClass1.....但紧接着就调用了__autoloadFunc;
 * 如果part2 before part1
 * 先查找__autoloadFunc, 找不到的话再去找__autoload
 * */
