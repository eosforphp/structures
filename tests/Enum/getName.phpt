--TEST--
Eos\DataStructures\Enum->getName();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Enum;

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
}

$fruit1 = new Fruit(Fruit::Apple);
var_dump($fruit1->getName());

$fruit2 = new Fruit(Fruit::Pear);
var_dump($fruit2->getName());

// too many args
try {
     $fruit1->getName(1);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
string(5) "Apple"
string(4) "Pear"
Eos\DataStructures\Enum::getName() expects exactly 0 parameters, 1 given