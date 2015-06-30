--TEST--
phpversion value
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
var_dump(phpversion('eos_datastructures'));
?>
--EXPECTF--
string(%d) "%d.%d.%d%s"
