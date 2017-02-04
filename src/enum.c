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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_exceptions.h>

#include "php_eos_datastructures.h"

zend_class_entry *ce_eos_datastructures_enum;
static zend_object_handlers eos_datastructures_enum_object_handlers;

/* enum object */
typedef struct _eos_datastructures_enum_object {
	zend_long   value;
	HashTable  *elements;
	zend_object std;
} eos_datastructures_enum_object;

#define EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(zv) ((eos_datastructures_enum_object*) \
	(((char*)Z_OBJ_P(zv)) - XtOffsetOf(eos_datastructures_enum_object, std)))

static int eos_datastructures_enum_apply_set(zend_long *option, int num_args, va_list args, zend_hash_key *hash_key);

/* ----------------------------------------------------------------
    Eos\Datastructures\Enum C API
------------------------------------------------------------------*/

/* {{{ function to take a zval** enum instance and give you back the long value */
PHP_EOS_DATASTRUCTURES_API zend_long php_eos_datastructures_get_enum_value(zval* enumclass)
{
	eos_datastructures_enum_object *enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(enumclass);
	return enum_object->value;
}
/* }}} */

/* {{{ function to take long and stick it in an enum class and validates it */
PHP_EOS_DATASTRUCTURES_API void php_eos_datastructures_set_enum_value(zval* enumclass, zend_long value)
{
	zend_bool found = 0;
	eos_datastructures_enum_object *enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(enumclass);

	/* handle the "easy" case of a long */
	zend_hash_apply_with_arguments(enum_object->elements,
		(apply_func_args_t)eos_datastructures_enum_apply_set, 2, &value, &found);

	if(found) {
		enum_object->value = value;
		return;
	} else {
		zend_throw_exception_ex(zend_ce_type_error, 0,
			"Value %d provided is not a const in enum %s",
			value, enum_object->std.ce->name->val);
	}
}
/* }}} */

/* {{{ function to validate a long against a ce */
PHP_EOS_DATASTRUCTURES_API zend_bool php_eos_datastructures_check_value(zend_class_entry *ce, zend_long value)
{
	zval *val;
	zend_bool return_value = 0;

	ZEND_HASH_FOREACH_VAL(&ce->constants_table, val) {
		if(Z_LVAL_P(val) == value) {
			return_value = 1;
			break;
		}
	} ZEND_HASH_FOREACH_END();

	if(!return_value) {
		zend_throw_exception_ex(zend_ce_type_error, 0,
			"Value %d provided is not a const in enum %s",
			value, ce->name->val);
	}
	return return_value;
}
/* }}} */

/* {{{ allows access to the enum class entry via other extensions */
PHP_EOS_DATASTRUCTURES_API zend_class_entry *php_eos_datastructures_get_enum_ce(void)
{
	return ce_eos_datastructures_enum;
}
/* }}} */

/* ----------------------------------------------------------------
    Eos\DataStructures\Enum class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Enum___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

/* {{{ proto void Enum->__construct(mixed value)
                  constructor for enum class, string can be a special case
                  anything else is cast and we attempt to assign */
PHP_METHOD(EosDataStructuresEnum, __construct)
{
	eos_datastructures_enum_object *enum_object;
	zend_bool found = 0;
	zval *name = NULL;
	zend_long constant_value;

	/* Pass 1 - check for a string value WITHOUT juggling */
	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z", &name)) {
		return;
	}

	enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(getThis());

	/* If we are given a string, look up a constant name */
	if(Z_TYPE_P(name) == IS_STRING) {
		zval *found_zval = zend_hash_find(enum_object->elements, Z_STR_P(name));
		if(found_zval) {
			enum_object->value = Z_LVAL_P(found_zval);
			return;
		}
		/* If this is NOT a numeric string, bail, otherwise continue */
		if(!is_numeric_string(Z_STRVAL_P(name), Z_STRLEN_P(name), NULL, NULL, 0)) {
			zend_throw_exception_ex(zend_ce_type_error, 0,
				"Name %s provided is not a const in enum %s",
				Z_STRVAL_P(name), enum_object->std.ce->name->val);
			return;
		}
	}

	/* Pass 2, so we didn't get a string, parse it hard as a long */
	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &constant_value)) {
		return;
	}
	/* handle the "easy" case of a long */
	zend_hash_apply_with_arguments(enum_object->elements,
		(apply_func_args_t)eos_datastructures_enum_apply_set, 2, &constant_value, &found);

	if(found) {
		enum_object->value = constant_value;
		return;
	}

	zend_throw_exception_ex(zend_ce_type_error, 0,
		"Value %d provided is not a const in enum %s",
		constant_value, enum_object->std.ce->name->val);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Enum_getName_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto string Enum->getName()
get member name of current enum value */
PHP_METHOD(EosDataStructuresEnum, getName)
{
	eos_datastructures_enum_object *enum_object;
	zend_ulong num_idx;
	zend_string *str_idx;
	zval *entry;
	zval tmp;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(getThis());

	ZEND_HASH_FOREACH_KEY_VAL(enum_object->elements, num_idx, str_idx, entry) {
		if(Z_LVAL_P(entry) == enum_object->value) {
			RETURN_STR_COPY(str_idx);
		}
	} ZEND_HASH_FOREACH_END();
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Enum_getElements_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto array Enum->getElements()
                   get array of available name => value pairs */
PHP_METHOD(EosDataStructuresEnum, getElements)
{
	eos_datastructures_enum_object *enum_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(getThis());

	array_init(return_value);
	zend_hash_copy(Z_ARRVAL_P(return_value), enum_object->elements, zval_add_ref);
}
/* }}} */

/* ----------------------------------------------------------------
    Eos\DataStructures\Enum Object management
------------------------------------------------------------------*/

/* {{{ */
static void eos_datastructures_enum_free_obj(zend_object *object)
{
	eos_datastructures_enum_object *intern = (eos_datastructures_enum_object*)
		((char*)object - XtOffsetOf(eos_datastructures_enum_object, std));

	if(!intern) {
		return;
	}
	intern->value = 0;
	zend_hash_destroy(intern->elements);
	FREE_HASHTABLE(intern->elements);

	zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ */
static zend_object* eos_datastructures_enum_obj_ctor(zend_class_entry *ce, eos_datastructures_enum_object **intern)
{
	eos_datastructures_enum_object *object = ecalloc(1, sizeof(eos_datastructures_enum_object)
												 + zend_object_properties_size(ce));

	object->value = 0;
	zend_update_class_constants(ce);

	zend_object_std_init(&object->std, ce);
	object->std.handlers = &eos_datastructures_enum_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

#if PHP_VERSION_ID < 70100
/* {{{ helper for construct to gather up constants */
static int eos_datastructures_enum_collect_constants(zval *constant_value, int num_args, va_list args, zend_hash_key *hash_key)
{
	HashTable *elements = va_arg(args, HashTable*);
	zend_string *classname = va_arg(args, zend_string*);

	if(Z_TYPE_P(constant_value) != IS_LONG) {
		php_error(E_WARNING, "Constant %s is being cast to an integer in Enum subclass %s", hash_key->key->val, classname->val);
		convert_to_long(constant_value);
	}

	zend_hash_add(elements, hash_key->key, constant_value);

	return ZEND_HASH_APPLY_KEEP;
}
/* }}} */
#endif

/* {{{ */
static zend_object* eos_datastructures_enum_create_object(zend_class_entry *ce)
{
	eos_datastructures_enum_object *intern = NULL;

	zend_object *return_value = eos_datastructures_enum_obj_ctor(ce, &intern);
	ALLOC_HASHTABLE(intern->elements);
	zend_hash_init(intern->elements, 8, NULL, NULL, 0);

#if PHP_VERSION_ID >= 70100
	int count = zend_hash_num_elements(&ce->constants_table);
	if (count > 0) {
		zend_string *key;
		zval *value;

		ZEND_HASH_FOREACH_STR_KEY_PTR(&ce->constants_table, key, value) {
			if(Z_TYPE_P(value) != IS_LONG) {
				php_error(E_WARNING, "Constant %s is being cast to an integer in Enum subclass %s", key->val, ce->name->val);
				convert_to_long(value);
			}

			zend_hash_add(intern->elements, key, value);
		} ZEND_HASH_FOREACH_END();
	}
#else
	zend_hash_apply_with_arguments(&ce->constants_table, (apply_func_args_t)eos_datastructures_enum_collect_constants, 2, intern->elements, ce->name);
#endif

	object_properties_init(&(intern->std), ce);
	return return_value;
}
/* }}} */

/* {{{ */
static zend_object* eos_datastructures_enum_clone_obj(zval *this_zval) 
{
	eos_datastructures_enum_object *new_enum;
	eos_datastructures_enum_object *old_enum = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(this_zval);
	zend_object *return_value = eos_datastructures_enum_obj_ctor(Z_OBJCE_P(this_zval), &new_enum);

	new_enum->value = old_enum->value;
	new_enum->elements = zend_array_dup(old_enum->elements);

	zend_objects_clone_members(&new_enum->std, &old_enum->std);

	return return_value;
}
/* }}} */

/* {{{ helper function for finding a valid enum value via long */
static int eos_datastructures_enum_apply_set(zend_long *option, int num_args, va_list args, zend_hash_key *hash_key) 
{
	zend_long *value = va_arg(args, zend_long*);
	zend_bool *found = va_arg(args, zend_bool*);

	if(*value == *option) {
		*found = 1;
		return ZEND_HASH_APPLY_STOP;
	}

	return ZEND_HASH_APPLY_KEEP;
}
/* }}} */

/* {{{ */
static void eos_datastructures_enum_object_set(zval *zobject, zval *value)
{
	eos_datastructures_enum_object *enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(zobject);
	zend_bool found = 0;
	zend_long lvalue;
	zval *juggled;

	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJ_HANDLER_P(value, get)) {
		zval rv;
		juggled = Z_OBJ_HANDLER_P(value, get)(value, &rv);
	} else {
		juggled = value;
	}

	/* if we have a string, do a zend_hash_find FIRST */
	if (Z_TYPE_P(juggled) == IS_STRING) {
		zval *found_zval =zend_hash_find(enum_object->elements, Z_STR_P(juggled));
		if(found_zval) {
			enum_object->value = Z_LVAL_P(found_zval);
			return;
		}
		/* If this is NOT a numeric string, bail, otherwise continue */
		if(!is_numeric_string(Z_STRVAL_P(juggled), Z_STRLEN_P(juggled), NULL, NULL, 0)) {
			zend_throw_exception_ex(zend_ce_type_error, 0,
				"Name %s provided is not a const in enum %s",
				Z_STRVAL_P(juggled), enum_object->std.ce->name->val);
			return;
		}
	}

	/* If juggled is long or a string, leave them alone, otherwise juggle */
	if (Z_TYPE_P(juggled) != IS_LONG) {
		convert_to_long(juggled);
	}
	lvalue = Z_LVAL_P(juggled);

	/* handle the "easy" case of a long */
	zend_hash_apply_with_arguments(enum_object->elements,
		(apply_func_args_t)eos_datastructures_enum_apply_set, 2, &lvalue, &found);

	if(found) {
		enum_object->value = lvalue;
		return;
	} else {
		zend_throw_exception_ex(zend_ce_type_error, 0,
		"Value %d provided is not a const in enum %s",
		lvalue, enum_object->std.ce->name->val);
	}
}
/* }}} */

/* {{{ */
static int eos_datastructures_enum_cast_object(zval *readobj, zval *writeobj, int type)
{
	eos_datastructures_enum_object *enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(readobj);

	ZVAL_LONG(writeobj, enum_object->value);
	convert_to_explicit_type(writeobj, type);
	return SUCCESS;
}
/* }}} */

/* {{{ */
static int eos_datastructures_enum_compare_objects(zval *z1, zval *z2)
{
	if (Z_TYPE_P(z1) == IS_OBJECT && Z_TYPE_P(z2) == IS_OBJECT &&
		instanceof_function(Z_OBJCE_P(z1), ce_eos_datastructures_enum) &&
		instanceof_function(Z_OBJCE_P(z2), ce_eos_datastructures_enum)) {

			eos_datastructures_enum_object *enum1 = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(z1);
			eos_datastructures_enum_object *enum2 = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(z2);

			return (enum1->value == enum2->value) ? 0 : ((enum1->value < enum2->value) ? -1 : 1);
		}

	return 1;
}
/* }}} */

/* {{{ */
static HashTable* eos_datastructures_enum_object_get_debug_info(zval *obj, int *is_temp)
{
	HashTable *debug_info, *std_props;
	zval elements, value;
	eos_datastructures_enum_object *enum_object = EOS_DATASTRUCTURES_ENUM_FETCH_OBJ(obj);

	std_props = zend_std_get_properties(obj);
	debug_info = zend_array_dup(std_props);

	array_init(&elements);
	zend_hash_copy(Z_ARRVAL(elements), enum_object->elements, zval_add_ref);
	zend_hash_str_add(debug_info, "__elements", sizeof("__elements") -1, &elements);

	ZVAL_LONG(&value, enum_object->value);
	zend_hash_str_add(debug_info, "__value", sizeof("__value")-1, &value);

	*is_temp = 1;
	return debug_info;
}
/* }}} */

/* ----------------------------------------------------------------
    Eos\DataStructures\Enum Definition and registration
------------------------------------------------------------------*/

/* {{{ class methods */
static const zend_function_entry eos_datastructures_enum_methods[] = {
	PHP_ME(EosDataStructuresEnum, __construct, Enum___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(EosDataStructuresEnum, getName, Enum_getName_args, ZEND_ACC_PUBLIC)
	PHP_ME(EosDataStructuresEnum, getElements, Enum_getElements_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(eos_datastructures_enum)
{
	zend_class_entry ce;

	memcpy(&eos_datastructures_enum_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	eos_datastructures_enum_object_handlers.offset = XtOffsetOf(eos_datastructures_enum_object, std);
	eos_datastructures_enum_object_handlers.free_obj = eos_datastructures_enum_free_obj;
	eos_datastructures_enum_object_handlers.clone_obj = eos_datastructures_enum_clone_obj;
	eos_datastructures_enum_object_handlers.cast_object = eos_datastructures_enum_cast_object;
	eos_datastructures_enum_object_handlers.compare_objects = eos_datastructures_enum_compare_objects;
	eos_datastructures_enum_object_handlers.get_debug_info = eos_datastructures_enum_object_get_debug_info;
	eos_datastructures_enum_object_handlers.set = eos_datastructures_enum_object_set;

	INIT_NS_CLASS_ENTRY(ce,  EOS_DATASTRUCTURES_NAMESPACE, "Enum", eos_datastructures_enum_methods);
	ce.create_object = eos_datastructures_enum_create_object;
	ce_eos_datastructures_enum = zend_register_internal_class(&ce);
	ce_eos_datastructures_enum->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

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
