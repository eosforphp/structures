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
#include "config.h"
#endif

#include <php.h>

#include "php_eos_datastructures.h"

zend_class_entry *ce_eos_datastructures_struct;
static zend_object_handlers eos_datastructures_struct_object_handlers;

/* ----------------------------------------------------------------
    Eos\Datastructures\Struct C API
------------------------------------------------------------------*/

/* {{{ allows access to the struct class entry via other extensions */
PHP_EOS_DATASTRUCTURES_API zend_class_entry *php_eos_datastructures_get_struct_ce(void)
{
	return ce_eos_datastructures_struct;
}
/* }}} */

/* ----------------------------------------------------------------
    Eos\DataStructures\Struct Object management
------------------------------------------------------------------*/

/* {{{ */
static zend_object* eos_datastructures_struct_create_object(zend_class_entry *ce)
{
	zend_object *object = zend_objects_new(ce);
	zend_object_std_init(object, ce);

	object->handlers = &eos_datastructures_struct_object_handlers;
	return object;
}
/* }}} */

/* ----------------------------------------------------------------
    Eos\DataStructures\Struct Definition and registration
------------------------------------------------------------------*/

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(eos_datastructures_struct)
{
	zend_class_entry ce;

	memcpy(&eos_datastructures_struct_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	//eos_datastructures_enum_object_handlers.offset = XtOffsetOf(eos_datastructures_enum_object, std);
	//eos_datastructures_enum_object_handlers.free_obj = eos_datastructures_enum_free_obj;
	//eos_datastructures_enum_object_handlers.clone_obj = eos_datastructures_enum_clone_obj;
	//eos_datastructures_enum_object_handlers.cast_object = eos_datastructures_enum_cast_object;
	//eos_datastructures_enum_object_handlers.compare_objects = eos_datastructures_enum_compare_objects;
	//eos_datastructures_enum_object_handlers.get_debug_info = eos_datastructures_enum_object_get_debug_info;
	//eos_datastructures_enum_object_handlers.set = eos_datastructures_enum_object_set;

	INIT_NS_CLASS_ENTRY(ce,  EOS_DATASTRUCTURES_NAMESPACE, "Struct", NULL);
	ce.create_object = eos_datastructures_struct_create_object;
	ce_eos_datastructures_struct = zend_register_internal_class(&ce);
	//ce_eos_datastructures_enum->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
