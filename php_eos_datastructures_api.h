/*
  +----------------------------------------------------------------------+
  | For PHP Version 7                                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015-2017 Elizabeth M Smith                            |
  +----------------------------------------------------------------------+
  | http://www.opensource.org/licenses/mit-license.php  MIT License      |
  | Also available in LICENSE                                            |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@gmail.com>                  |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_EOS_DATASTRUCTURES_API_H
#define PHP_EOS_DATASTRUCTURES_API_H

/* Public C api for use by other extensions */

#include <php.h>

#define PHP_EOS_DATASTRUTCURES_API_VERSION "1.0.0"

zend_class_entry *php_eos_datastructures_get_enum_ce(void);
long php_eos_datastructures_get_enum_value(zval* enumclass);
void php_eos_datastructures_set_enum_value(zval* enumclass, long value);
zend_bool php_eos_datastructures_check_value(zend_class_entry *ce, long value);

/* C apis for enums will go here */

#endif /* PHP_EOS_DATASTRUCTURES_API_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
