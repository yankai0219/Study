<?php
$xml_string = <<<XML
<?xml version="1.0" encoding="UTF-8"?>
<root>
   <item id="foo"> hello </item>
</root>
XML;

#$root = new SimpleXMLElement($xml_string); // method 1
$root = simplexml_load_string($xml_string); // method 2
$root->item->addAttribute('xx', 'bar');
$root->item->addChild('item_child', 'item_child');
$root->addChild('item_brother', 'item_brother');
$root->item_brother->addAttribute('brother', 'big');
echo $root->asXML();
?>
