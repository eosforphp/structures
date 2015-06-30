/*
  +----------------------------------------------------------------------+
  | For PHP Version 7                                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 Elizabeth M Smith                                 |
  +----------------------------------------------------------------------+
  | http://www.opensource.org/licenses/mit-license.php  MIT License      |
  | Also available in LICENSE                                            |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@gmail.com>                  |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include <php.h>

#include "php_eos_datastructures.h"
#include "php_eos_datastructures_internal.h"

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(eos_datastructures)
{
	PHP_MINIT(eos_datastructures_enum)(INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(eos_datastructures)
{
	php_info_print_table_start();
	php_info_print_table_colspan_header(2, "Eos Datastructures");
	php_info_print_table_row(2, "Extension", "enabled");
	php_info_print_table_row(2, "Type",
#ifdef COMPILE_DL_EOS_DATASTRUCTURES
		"compiled as dynamic module"
#else
		"compiled as static module"
#endif
        );
	php_info_print_table_colspan_header(2, "DataTypes Available");
	php_info_print_table_row(2, "Enum Support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ datastructures_module_entry */
zend_module_entry eos_datastructures_module_entry = {
	STANDARD_MODULE_HEADER,
	"eos_datastructures",
	NULL,
	PHP_MINIT(eos_datastructures),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(eos_datastructures),
	PHP_EOS_DATASTRUCTURES_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EOS_DATASTRUCTURES
	ZEND_GET_MODULE(eos_datastructures)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */