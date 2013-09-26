
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include "php_ext.h"
#include "peregrin.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"

zend_class_entry *peregrin_version_ce;

ZEND_DECLARE_MODULE_GLOBALS(peregrin)

PHP_MINIT_FUNCTION(peregrin){

	ZEPHIR_INIT(Peregrin_Version);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(peregrin){

	assert(ZEPHIR_GLOBAL(function_cache) == NULL);
	//assert(ZEPHIR_GLOBAL(orm).parser_cache == NULL);
	//assert(ZEPHIR_GLOBAL(orm).ast_cache == NULL);

	return SUCCESS;
}
#endif

static PHP_RINIT_FUNCTION(peregrin){

	php_zephir_init_globals(ZEPHIR_VGLOBAL TSRMLS_CC);
	//peregrin_init_interned_strings(TSRMLS_C);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(peregrin){

	if (ZEPHIR_GLOBAL(start_memory) != NULL) {
		zephir_clean_restore_stack(TSRMLS_C);
	}

	if (ZEPHIR_GLOBAL(function_cache) != NULL) {
		zend_hash_destroy(ZEPHIR_GLOBAL(function_cache));
		FREE_HASHTABLE(ZEPHIR_GLOBAL(function_cache));
		ZEPHIR_GLOBAL(function_cache) = NULL;
	}

	return SUCCESS;
}

static PHP_MINFO_FUNCTION(peregrin)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Version", PHP_PEREGRIN_VERSION);
	php_info_print_table_end();
}

static PHP_GINIT_FUNCTION(peregrin)
{
	zephir_memory_entry *start;

	php_zephir_init_globals(peregrin_globals TSRMLS_CC);

	/* Start Memory Frame */
	start = (zephir_memory_entry *) pecalloc(1, sizeof(zephir_memory_entry), 1);
	start->addresses       = pecalloc(24, sizeof(zval*), 1);
	start->capacity        = 24;
	start->hash_addresses  = pecalloc(8, sizeof(zval*), 1);
	start->hash_capacity   = 8;

	peregrin_globals->start_memory = start;

	/* Global Constants */
	ALLOC_PERMANENT_ZVAL(peregrin_globals->global_false);
	INIT_PZVAL(peregrin_globals->global_false);
	ZVAL_FALSE(peregrin_globals->global_false);
	Z_ADDREF_P(peregrin_globals->global_false);

	ALLOC_PERMANENT_ZVAL(peregrin_globals->global_true);
	INIT_PZVAL(peregrin_globals->global_true);
	ZVAL_TRUE(peregrin_globals->global_true);
	Z_ADDREF_P(peregrin_globals->global_true);

	ALLOC_PERMANENT_ZVAL(peregrin_globals->global_null);
	INIT_PZVAL(peregrin_globals->global_null);
	ZVAL_NULL(peregrin_globals->global_null);
	Z_ADDREF_P(peregrin_globals->global_null);
}

static PHP_GSHUTDOWN_FUNCTION(peregrin)
{
	assert(peregrin_globals->start_memory != NULL);

	pefree(peregrin_globals->start_memory->hash_addresses, 1);
	pefree(peregrin_globals->start_memory->addresses, 1);
	pefree(peregrin_globals->start_memory, 1);
	peregrin_globals->start_memory = NULL;
}

zend_module_entry peregrin_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_PEREGRIN_EXTNAME,
	NULL,
	PHP_MINIT(peregrin),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(peregrin),
#else
	NULL,
#endif
	PHP_RINIT(peregrin),
	PHP_RSHUTDOWN(peregrin),
	PHP_MINFO(peregrin),
	PHP_PEREGRIN_VERSION,
	ZEND_MODULE_GLOBALS(peregrin),
	PHP_GINIT(peregrin),
	PHP_GSHUTDOWN(peregrin),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_PEREGRIN
ZEND_GET_MODULE(peregrin)
#endif
