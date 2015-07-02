--TEST--
eos_datastructures class listing
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('eos_datastructures');
var_dump($ext->getClassNames());
?>
--EXPECT--
array(2) {
  [0]=>
  string(23) "Eos\DataStructures\Enum"
  [1]=>
  string(25) "Eos\DataStructures\Struct"
}
