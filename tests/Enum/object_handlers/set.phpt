--TEST--
Eos\DataStructures\Enum set handler
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
    const Banana = 3;
}

$fruit = new Fruit(Fruit::Apple);
var_dump($fruit);

$fruit = Fruit::Pear;
var_dump($fruit);

$fruit = new Fruit(Fruit::Apple);
$fruit = 'Banana';
var_dump($fruit);

// bad value, bad
try {
     $fruit = 8;
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
     $fruit = 'grape';
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Fruit)#%d (2) {
  ["__elements"]=>
  array(3) {
    ["Apple"]=>
    int(1)
    ["Pear"]=>
    int(2)
    ["Banana"]=>
    int(3)
  }
  ["__value"]=>
  int(1)
}
object(Fruit)#%d (2) {
  ["__elements"]=>
  array(3) {
    ["Apple"]=>
    int(1)
    ["Pear"]=>
    int(2)
    ["Banana"]=>
    int(3)
  }
  ["__value"]=>
  int(2)
}
object(Fruit)#%d (2) {
  ["__elements"]=>
  array(3) {
    ["Apple"]=>
    int(1)
    ["Pear"]=>
    int(2)
    ["Banana"]=>
    int(3)
  }
  ["__value"]=>
  int(3)
}
Value 8 provided is not a const in enum Fruit
Name grape provided is not a const in enum Fruit