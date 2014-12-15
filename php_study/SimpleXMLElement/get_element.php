<?php
// //Method1
// include 'xml_file.php';
// $movies = new SimpleXMLElement($xmlstr);

// //Method2
$filePath = dirname(__FILE__) . '/xml_file.xml';
$movies = simplexml_load_file($filePath);                    // root node
echo 'count($movie) should be 2:' . count($movies->movie) . "\n";

$movie0 = $movies->movie[0];                                // case d)
echo 'title:' . $movie0->title . "\n";                      // case b)
echo 'count($character) should be 2:' . count($movie0->characters->character) . "\n";
$character0 = $movie0->characters->character[0];
echo 'character name:' . $character0->name . "\n";

echo 'plot:' . $movie0->plot . "\n";
echo 'great-lines:' . $movie0->{'great-lines'}->line . "\n"; // case c)
echo 'rating type:' . $movie0->rating[0]['type'];            // case e)
echo 'value:' . $movie0->rating[0] . "\n";

$movie1 = $movies->movie[1];
echo 'title:' . $movie1->title. "\n";

// Simplexmlelement implements Traversable Interface, so foreach can be used
foreach ($movies as $movie)
{
    echo 'title:' . $movie->title . "\n";
    echo 'great-lines:' . $movie->{'great-lines'}->line . "\n";
    echo 'rating type' . $movie->rating[0]['type'] . ',value:' . $movie->rating[0] . "\n";
}
