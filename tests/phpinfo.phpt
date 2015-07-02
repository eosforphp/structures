--TEST--
eos_datastructures phpinfo information
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('eos_datastructures');
$ext->info();
?>
--EXPECTF--
eos_datastructures

                            Eos Datastructures                            
Extension => enabled
Type => compiled as %s module
                           DataTypes Available                           
Enum Support => enabled
Struct Support => enabled