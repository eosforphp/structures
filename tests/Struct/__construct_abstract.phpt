--TEST--
Eos\DataStructures\Struct is abstract
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Struct;

try {
    $item = new Struct;
} catch (Error $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
Cannot instantiate abstract class Eos\DataStructures\Struct