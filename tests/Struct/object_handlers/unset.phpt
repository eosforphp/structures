--TEST--
Eos\DataStructures\Struct unset handler
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

// bad value, bad
try {
     unset($fruit->apple);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Name apple provided is a property in struct Fruit and cannot be unset