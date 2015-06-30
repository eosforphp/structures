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

#ifndef PHP_EOS_DATASTRUCTURES_EXT_H
#define PHP_EOS_DATASTRUCTURES_EXT_H

#include <php.h>

extern zend_module_entry eos_datastructures_module_entry;
#define phpext_eos_datastructures_ptr &eos_datastructures_module_entry

#define PHP_EOS_DATASTRUCTURES_VERSION "0.1.0-dev"
#define EOS_DATASTRUCTURES_NAMESPACE "Eos\\DataStructures"

#ifdef PHP_WIN32
#   define PHP_EOS_DATASTRUCTURES_API __declspec(dllexport)
#elif defined(__GNUCC__) && __GNUC__ >= 4
#   define PHP_EOS_DATASTRUCTURES_API extern __attribute__ ((visibility("default")))
#else
#   define PHP_EOS_DATASTRUCTURES_API extern
#endif

#endif /* PHP_EOS_DATASTRUCTURES_EXT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
