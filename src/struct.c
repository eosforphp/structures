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
#include <zend_exceptions.h>

#include "php_eos_datastructures.h"

/**
 * Struct
 * Immutable\Struct
 * Typed\Struct
 */
zend_class_entry *ce_eos_datastructures_struct;
zend_class_entry *ce_eos_datastructures_immutable_struct;
zend_class_entry *ce_eos_datastructures_typed_struct;

static zend_object_handlers eos_datastructures_struct_object_handlers;
static zend_object_handlers eos_datastructures_immutable_struct_object_handlers;
static zend_object_handlers eos_datastructures_typed_struct_object_handlers;



static void eos_datastructure_struct_object_write_property(zval *object, zval *member, zval *value, void **cache_slot);

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
    Eos\DataStructures\Struct class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(Struct___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_INFO(0, values)
ZEND_END_ARG_INFO()

/* {{{ proto void Struct->__construct(array/object values)
                  constructor for struct class, will walk hashtable key/values to set properties */
PHP_METHOD(EosDataStructuresStruct, __construct)
{
	HashTable *values = NULL;
	zend_string *str_idx;
	zval *entry;

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "|H", &values)) {
		return;
	}

	/**
	 * Our arguments hashtable has two different behaviors
	 * If we are in the generic struct class, we set each item
	 * as a public property
	 *
	 * If we are in an extended class, we set only existing properties
	 */
	if(values) {

		if(Z_OBJCE_P(getThis()) == ce_eos_datastructures_struct) {

			ZEND_HASH_FOREACH_STR_KEY_VAL(values, str_idx, entry) {
				if(str_idx) {
					zval member;
					ZVAL_STR(&member, str_idx);
					(zend_get_std_object_handlers())->write_property(getThis(), &member, entry, NULL);
					zval_dtor(&member);
				}
			} ZEND_HASH_FOREACH_END();

		} else {

			/* mangle scope so we can get to private/protected */
			zend_class_entry *old_scope = EG(scope);
			EG(scope) = Z_OBJCE_P(getThis());

			ZEND_HASH_FOREACH_STR_KEY_VAL(values, str_idx, entry) {
				if(str_idx) {
					zval member;
					ZVAL_STR(&member, str_idx);
					eos_datastructure_struct_object_write_property(getThis(), &member, entry, NULL);
					zval_dtor(&member);
				}
			} ZEND_HASH_FOREACH_END();

			/* return our scope to normal */
			EG(scope) = old_scope;

		}
	}
}

/* ----------------------------------------------------------------
    Eos\DataStructures\Struct Object management
------------------------------------------------------------------*/

/* {{{ */
static zend_object* eos_datastructures_struct_create_object(zend_class_entry *ce)
{
	zend_object *object = zend_objects_new(ce);
	zend_object_std_init(object, ce);
	object_properties_init(object, ce);

	object->handlers = &eos_datastructures_struct_object_handlers;
	return object;
}
/* }}} */

/**
 * Helper for property exists lookup for limiting properties to declared
 * or declared with constructor for generics
 */
static inline zend_bool eos_datastructures_struct_property_exists(zval *object, zval *member) {
	int ret = 0;

	/**
	 * Generic structs are "property is already set"
	 */
	if(Z_OBJCE_P(object) == ce_eos_datastructures_struct) {
		ret = (zend_get_std_object_handlers())->has_property(object, member, 0, NULL);
	} else {
		zend_property_info *property_info;
		/* mangle scope so we can get to private/protected */
		zend_class_entry *old_scope = EG(scope);
		EG(scope) = Z_OBJCE_P(object);

		property_info = zend_get_property_info(Z_OBJCE_P(object), Z_STR_P(member), 1);
		if(property_info!= ZEND_WRONG_PROPERTY_INFO &&
		   property_info &&
		   (property_info->flags & ZEND_ACC_STATIC) == 0) {
			ret = 1;
		}
		/* return our scope to normal */
		EG(scope) = old_scope;
	}

	return ret;
}

/* {{{ */
static void eos_datastructure_struct_object_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
	zval tmp_member;

	if(Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		cache_slot = NULL;
	}

	if(eos_datastructures_struct_property_exists(object, member)) {
		/* This exists */
		(zend_get_std_object_handlers())->write_property(object, member, value, cache_slot);
	} else {
		zend_throw_exception_ex(zend_ce_type_error, 0,
			"Name %s provided is not a property in struct %s",
			Z_STRVAL_P(member), Z_OBJCE_P(object)->name->val);
	}

	if(member == &tmp_member) {
		zval_dtor(member);
	}
}
/* }}} */

/* {{{ */
static zval *eos_datastructure_struct_object_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
	zval tmp_member;
	zval *retval = NULL;

	if(Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		cache_slot = NULL;
	}

	/* mangle scope so we can get to private/protected */
	zend_class_entry *old_scope = EG(scope);
	EG(scope) = Z_OBJCE_P(object);

	retval= (zend_get_std_object_handlers())->read_property(object, member, type, cache_slot, rv);

	/* return our scope to normal */
	EG(scope) = old_scope;

	if(member == &tmp_member) {
		zval_dtor(member);
	}

	return retval;
}
/* }}} */

/* {{{ */
static void eos_datastructure_struct_object_unset_property(zval *object, zval *member, void **cache_slot)
{
	zval tmp_member;

	if(Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		cache_slot = NULL;
	}

	if(eos_datastructures_struct_property_exists(object, member)) {
		zend_throw_exception_ex(zend_ce_type_error, 0,
			"Name %s provided is a property in struct %s and cannot be unset",
			Z_STRVAL_P(member), Z_OBJCE_P(object)->name->val);
	} else {
		/* we shouldn't ever hit this, but just in case */
		(zend_get_std_object_handlers())->unset_property(object, member, cache_slot);
	}

	if(member == &tmp_member) {
		zval_dtor(member);
	}
}
/* }}} */

/* ----------------------------------------------------------------
    Eos\DataStructures\Struct Definition and registration
------------------------------------------------------------------*/

/* {{{ class methods */
static const zend_function_entry eos_datastructures_struct_methods[] = {
	PHP_ME(EosDataStructuresStruct, __construct, Struct___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(eos_datastructures_struct)
{
	zend_class_entry ce;

	memcpy(&eos_datastructures_struct_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	eos_datastructures_struct_object_handlers.write_property = eos_datastructure_struct_object_write_property;
	eos_datastructures_struct_object_handlers.read_property = eos_datastructure_struct_object_read_property;
	eos_datastructures_struct_object_handlers.get_property_ptr_ptr = NULL;
	eos_datastructures_struct_object_handlers.get_method = NULL;
	eos_datastructures_struct_object_handlers.unset_property = eos_datastructure_struct_object_unset_property;

	INIT_NS_CLASS_ENTRY(ce,  EOS_DATASTRUCTURES_NAMESPACE, "Struct", eos_datastructures_struct_methods);
	ce.create_object = eos_datastructures_struct_create_object;
	ce_eos_datastructures_struct = zend_register_internal_class(&ce);

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
