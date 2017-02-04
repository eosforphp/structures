--TEST--
Eos\DataStructures\Struct set handler
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Struct;

class Fruit extends Struct {
   public $apple;
   public $banana;
   public $pear;
}

$fruit = new Fruit();
var_dump($fruit);

$fruit = new Fruit(['banana' => 2]);
var_dump($fruit);

$fruit = new Fruit;
$fruit->apple = 7;
var_dump($fruit);

// bad value, bad
try {
     $fruit->grape = 4;
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Fruit)#%d (3) {
  ["apple"]=>
  NULL
  ["banana"]=>
  NULL
  ["pear"]=>
  NULL
}
object(Fruit)#%d (3) {
  ["apple"]=>
  NULL
  ["banana"]=>
  int(2)
  ["pear"]=>
  NULL
}
object(Fruit)#%d (3) {
  ["apple"]=>
  int(7)
  ["banana"]=>
  NULL
  ["pear"]=>
  NULL
}
Name grape provided is not a property in struct Fruit
