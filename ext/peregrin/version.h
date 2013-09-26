
extern zend_class_entry *peregrin_version_ce;

ZEPHIR_INIT_CLASS(Peregrin_Version);

PHP_METHOD(Peregrin_Version, _getVersion);
PHP_METHOD(Peregrin_Version, get);
PHP_METHOD(Peregrin_Version, getId);

ZEPHIR_INIT_FUNCS(peregrin_version_method_entry) {
	PHP_ME(Peregrin_Version, _getVersion, NULL, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Peregrin_Version, get, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Peregrin_Version, getId, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
