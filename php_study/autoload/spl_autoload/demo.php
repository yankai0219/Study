<?php
$path = dirname(__FILE__);
include_once "$path/auto_load.php";

$con1 = new controller_con1();
$mod1 = new model_Mod1();
$view = new view_View1();

controller_Con1::test1();
