--TEST--
Eos\DataStructures\Struct->__construct();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Struct;

$item = new Struct(['item' => 'value']);

var_dump($item);

$item->item = 'newvalue';

var_dump($item);

try {
    $item->foo = 'bar';
} catch (Error $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
object(Eos\DataStructures\Struct)#%d (1) {
  ["item"]=>
  string(5) "value"
}
object(Eos\DataStructures\Struct)#%d (1) {
  ["item"]=>
  string(8) "newvalue"
}
Name foo provided is not a property in struct Eos\DataStructures\Struct