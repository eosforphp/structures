--TEST--
Eos\DataStructures\Struct get handler
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Struct;

class Fruit extends Struct {
   public $apple;
   protected $banana;
   private $pear;
}

$fruit = new Fruit(['banana' => 2,
                    'apple' => 1,
                    'pear' => 3
                    ]);

echo $fruit->pear, PHP_EOL;

// haha, immutable, you cannot write!
try {
     $fruit->pear = 2;
} catch (Error $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
3
Cannot access private property Fruit::$pear