PHP_ARG_ENABLE(peregrin, whether to enable peregrin, [ --enable-peregrin   Enable Peregrin])

if test "$PHP_PEREGRIN" = "yes"; then
	AC_DEFINE(HAVE_PEREGRIN, 1, [Whether you have Peregrin])
	peregrin_sources="peregrin.c kernel/main.c kernel/memory.c kernel/exception.c kernel/hash.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/alternative/fcall.c kernel/operators.c kernel/concat.c peregrin/version.c"
	PHP_NEW_EXTENSION(peregrin, $peregrin_sources, $ext_shared)
fi
