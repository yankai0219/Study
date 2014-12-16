<?php
// php 不同系统的换行
//不同系统之间换行的实现是不一样的
//linux 与unix中用 /n
//MAC 用 /r
//window 为了体现与linux不同 则是 /r/n
//所以在不同平台上 实现方法就不一样
//php 有三种方法来解决

//1、使用str_replace 来替换换行
$str = "hello\n\r\n";
var_dump($str);
$newstr = str_replace(array("\r\n", "\r", "\n"), "", $str);
var_dump($newstr);

//2、使用正则替换
$newstr = preg_replace('#\s*#', '', $str);
var_dump($newstr);

//3、使用php定义好的变量 （建议使用）
$newstr = str_replace(PHP_EOL, '', $str);
var_dump($newstr);
