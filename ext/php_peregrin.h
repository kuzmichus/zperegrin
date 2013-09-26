
#ifndef PHP_PEREGRIN_H
#define PHP_PEREGRIN_H 1

#include "kernel/globals.h"

#define PHP_PEREGRIN_VERSION "0.0.1"
#define PHP_PEREGRIN_EXTNAME "peregrin"

ZEND_BEGIN_MODULE_GLOBALS(peregrin)

	/* Memory */
	zephir_memory_entry *start_memory;
	zephir_memory_entry *active_memory;

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/* Function cache */
	HashTable *function_cache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;

ZEND_END_MODULE_GLOBALS(peregrin)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(peregrin)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(peregrin_globals_id, zend_peregrin_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (peregrin_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_peregrin_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(peregrin_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(peregrin_globals)
#endif

#define zephir_globals peregrin_globals
#define zend_zephir_globals zend_peregrin_globals

extern zend_module_entry peregrin_module_entry;
#define phpext_peregrin_ptr &peregrin_module_entry

#endif
