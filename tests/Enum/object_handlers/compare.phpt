--TEST--
Eos\DataStructures\Enum compare objects handler
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Enum;

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
    const Orange = 3;
    const Banana = 4;
}

$fruit1 = new Fruit(Fruit::Apple);
$fruit2 = new Fruit(Fruit::Pear);
$fruit3 = new Fruit(Fruit::Apple);

var_dump($fruit1 > $fruit2);
var_dump($fruit1 < $fruit2);
var_dump($fruit1 < 2);

var_dump($fruit1 == $fruit2);
var_dump($fruit1 == $fruit3);
var_dump($fruit1 === 1);
var_dump($fruit1 == 1);

?>
--EXPECT--
bool(false)
bool(true)
bool(true)
bool(false)
bool(true)
bool(false)
bool(true)