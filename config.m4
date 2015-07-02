dnl
dnl Eos\DataStructures for PHP7
dnl

PHP_ARG_WITH(eos_datastructures, Additional Datastructures for PHP7,
[  --with-eos_datastructures            Enable datastructure support], yes)

if test "$PHP_EOS_DATASTRUCTURES" != "no"; then

  PHP_NEW_EXTENSION(eos_datastructures, \
    src/eos_datastructures.c \
    src/enum.c \
    src/struct.c \
  , $ext_shared)

  PHP_INSTALL_HEADERS([ext/eos_datastructures], [php_eos_datastructures_api.h])
  
fi
