--TEST--
Eos\DataStructures\Struct get_method handler
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Struct;

class Fruit extends Struct {
   public $apple;
   
   public function pear() {
      echo "boo";
   }
}

$fruit = new Fruit();
var_dump($fruit);

// bad value, bad
try {
     $fruit->pear();
} catch (Error $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Fruit)#%d (1) {
  ["apple"]=>
  NULL
}
Object does not support method calls