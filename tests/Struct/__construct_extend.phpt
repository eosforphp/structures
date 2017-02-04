--TEST--
Eos\DataStructures\Struct extended
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Struct;

class Test extends Struct {
 const foo = 1;
}

$item = new Test(1);

/*
try {
    $item = new Test(1);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

// only 1 arg
try {
    $item = new Test([],2);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

class Fruit extends Struct {
    public $apple;
    public $pear;
}

try {
    $badfruit = new Fruit(['badfruit' => 'foo']);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

$fruit = new Fruit(['apple' => 1, 'pear' => 2]);
var_dump($fruit);

$fruit = new Fruit();
var_dump($fruit);

$fruit->apple = 1;
$fruit->pear = 5;
var_dump($fruit); */
?>
--EXPECTF--
Eos\DataStructures\Struct::__construct() expects parameter 1 to be array, integer given
Eos\DataStructures\Struct::__construct() expects at most 1 parameter, 2 given
Name badfruit provided is not a property in struct Fruit
object(Fruit)#%d (2) {
  ["apple"]=>
  int(1)
  ["pear"]=>
  int(2)
}
object(Fruit)#%d (2) {
  ["apple"]=>
  NULL
  ["pear"]=>
  NULL
}
object(Fruit)#%d (2) {
  ["apple"]=>
  int(1)
  ["pear"]=>
  int(5)
}
