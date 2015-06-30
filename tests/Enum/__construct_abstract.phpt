--TEST--
Eos\DataStructures is abstract
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Eos\DataStructures\Enum;

try {
    $item = new Enum;
} catch (Error $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
Cannot instantiate abstract class Eos\DataStructures\Enum