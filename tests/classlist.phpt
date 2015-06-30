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
array(1) {
  [0]=>
  string(23) "Eos\DataStructures\Enum"
}
