--TEST--
Eos\DataStructures\Enum->__construct();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Enum;

class Test extends Enum {}

try {
    $item = new Test(1);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
}

try {
    $badfruit = new Fruit('apple');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $badfruit2 = new Fruit(6);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

echo new Fruit('Apple'), PHP_EOL;
echo new Fruit(Fruit::Apple), PHP_EOL;
echo new Fruit(1.0), PHP_EOL;

echo new Fruit('Pear'), PHP_EOL;
echo new Fruit(Fruit::Pear), PHP_EOL;
echo new Fruit('2'), PHP_EOL;

// requires at least 1 arg
try {
    $badfruit3 = new Fruit;
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Value 1 provided is not a const in enum Test
Name apple provided is not a const in enum Fruit
Value 6 provided is not a const in enum Fruit
1
1
1
2
2
2
Eos\DataStructures\Enum::__construct() expects exactly 1 parameter, 0 given