# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(cwdaemon, 0.13.0, acerion@wp.pl)
AM_INIT_AUTOMAKE([subdir-objects])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/cwdaemon.c])
AC_PROG_GCC_TRADITIONAL
AC_PROG_RANLIB # Because of utility library built in in tests/library/
AC_CONFIG_HEADERS([config.h])
PKG_PROG_PKG_CONFIG # Don't call pkg-config directly. Use $PKG_CONFIG.


# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_CHECK_PROGS(RPMBUILD, rpmbuild, rpm)
AM_PROG_CC_C_O # per-target flags in src/Makefile.am

# Checks for libraries.



# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h fcntl.h \
stdlib.h string.h strings.h sys/ioctl.h sys/socket.h \
sys/time.h time.h signal.h stdarg.h termios.h sys/resource.h \
sys/stat.h])

# Line-printer (parallel port printer) headers.
AC_CHECK_HEADERS([linux/ppdev.h dev/ppbus/ppi.h])

# getopt_long()
AC_CHECK_HEADERS([getopt.h])



# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([socket strerror setpriority])


# Needed to have access to local cwdaemon binary that will be tested during
# "make check". "local" meaning a binary that has not been put into
# $prefix/sbin yet.
AC_SUBST([ABS_TOP_BUILDDIR], [abs_top_builddir])



# This is just a default value that can be overriden later.
default_tests_tty_cwdevice_name="ttyUSB0"



AC_CANONICAL_HOST
case $host_os in
    *linux*|*Linux*)
	AC_MSG_NOTICE([Detected Linux: $host_os])
	# Example value of host_os: 'linux-gnu'
	#
	# Name of first tty device (USB-to-UART converter) on Linux. User
	# group: dialout.
	default_tests_tty_cwdevice_name="ttyUSB0"
	;;

	*freebsd*|*FreeBSD*)
	AC_MSG_NOTICE([Detected FreeBSD: $host_os])
	# Example value of host_os: 'freebsd13.2'.
	#
	# Name of first tty device (USB-to-UART converter) on FreeBSD 13.2.
	# User group: dialer.
	default_tests_tty_cwdevice_name="cuau0"
	;;

	*openbsd*|*OpenBSD*)
	AC_MSG_NOTICE([Detected OpenBSD: $host_os])
	;;

	*netbsd*|*NetBSD*)
	# I didn't test unixcw on NetBSD, but let's give it a
	# chance.
	AC_MSG_NOTICE([Detected NetBSD: $host_os])
	;;

	*)
	AC_MSG_NOTICE([Detected other OS: $host_os])
	;;
esac




# For debug purposes only.
# CFLAGS=`echo "$CFLAGS" | sed 's/-O2/-O0/g'`

# TODO acerion 2024.04.12: include these flags and fix warnings:
#   CFLAGS="${CFLAGS} -Wconversion -Wsign-conversion -Wint-conversion"

CFLAGS="${CFLAGS} -D_FORTIFY_SOURCE=2"
CFLAGS="${CFLAGS} -std=c99"
if test "${ac_cv_c_compiler_gnu}" = "yes"; then
  CFLAGS="${CFLAGS} -Wall -Wextra -pedantic"
  CFLAGS="${CFLAGS} -Wswitch-default -Wswitch-enum"
  CFLAGS="${CFLAGS} -Wimplicit-function-declaration -Wimplicit-int"
  CFLAGS="${CFLAGS} -Wpointer-arith -Wpointer-sign"
  CFLAGS="${CFLAGS} -Wfloat-equal -Wcast-qual -Wwrite-strings"
  CFLAGS="${CFLAGS} -Wmissing-prototypes -Wstrict-prototypes"
  CFLAGS="${CFLAGS} -Wmissing-declarations -Wredundant-decls"
  CFLAGS="${CFLAGS} -Wundef"
  CFLAGS="${CFLAGS} -Wunused -Wunused-macros -Wunused-result"
  CFLAGS="${CFLAGS} -Wmisleading-indentation"
  CFLAGS="${CFLAGS} -Wuninitialized -Winit-self -Wstrict-aliasing -Wattributes -Wmain"
  CFLAGS="${CFLAGS} -Wincompatible-pointer-types -Wold-style-definition"

  # https://kristerw.blogspot.com/2017/09/useful-gcc-warning-options-not-enabled.html
  CFLAGS="${CFLAGS} -Wnull-dereference -Wdouble-promotion"
  CFLAGS="${CFLAGS} -Wshadow -Wformat=2"
fi

# clang 14.0.6 on Debian 12 doesn't recognize these options.
if test "$CC" = "gcc" ; then
  CFLAGS="${CFLAGS} -Walloc-zero -Wformat-signedness"
  # https://kristerw.blogspot.com/2017/09/useful-gcc-warning-options-not-enabled.html
  CFLAGS="${CFLAGS} -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wjump-misses-init"
fi




# Build functional tests? No by default.
AC_ARG_ENABLE(functional_tests,
    AS_HELP_STRING([--enable-functional-tests], [enable functional tests of cwdaemon]),
    [],
    [enable_functional_tests=no])

AC_MSG_CHECKING([whether to build cwdaemon's functional tests])
if test x$enable_functional_tests = xyes ; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi
AM_CONDITIONAL([FUNCTIONAL_TESTS], [test x$enable_functional_tests = xyes])
AC_SUBST(FUNCTIONAL_TESTS)




# Run long functional tests? No by default.
AC_ARG_ENABLE(long_functional_tests,
    AS_HELP_STRING([--enable-long-functional-tests], [run long functional tests of cwdaemon]),
    [],
    [enable_long_functional_tests=no])

AC_MSG_CHECKING([whether to run cwdaemon's long functional tests])
if test x$enable_long_functional_tests = xyes ; then
    AC_MSG_RESULT(yes)
	AC_DEFINE([TESTS_RUN_LONG_FUNCTIONAL_TESTS], [1], [Whether to run long functional tests.])
else
    AC_MSG_RESULT(no)
	AC_DEFINE([TESTS_RUN_LONG_FUNCTIONAL_TESTS], [0], [Whether to run long functional tests.])
fi




# Path to cwdaemon binary that will be used as local test instance of cwdaemon server.
tests_cwdaemon_path=$ac_pwd/src/cwdaemon
AC_ARG_WITH([tests_cwdaemon_path],
            [AS_HELP_STRING([--with-tests-cwdaemon-path=STRING],
                            [specify a path to cwdaemon binary used in functional tests])],
            [tests_cwdaemon_path="$withval"], [])
# The next line will write a #define into ROOT/config.h.
AC_DEFINE_UNQUOTED([TESTS_CWDAEMON_PATH],["${tests_cwdaemon_path}"],[Path to cwdaemon binary used in functional tests.])




# Name of tty cwdevice that will be used by local test instance of cwdaemon
# server.
tests_tty_cwdevice_name=$default_tests_tty_cwdevice_name
AC_ARG_WITH([tests_tty_cwdevice_name],
            [AS_HELP_STRING([--with-tests-tty-cwdevice-name=STRING],
                            [specify a mame of tty cwdevice used in functional tests])],
            [tests_tty_cwdevice_name="$withval"], [])
# The next line will write a #define into ROOT/config.h.
AC_DEFINE_UNQUOTED([TESTS_TTY_CWDEVICE_NAME],["${tests_tty_cwdevice_name}"],[Name of tty cwdevice used in functional tests.])




# Run code coverage tool?
AC_ARG_ENABLE(gcov,
    AS_HELP_STRING([--enable-gcov], [enable gcov code coverage report for unit tests of cwdaemon]),
    [],
    [enable_gcov=no])

AC_MSG_CHECKING([whether to enable gcov unit for tests for cwdaemon])
if test x$enable_gcov = xyes ; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi
AM_CONDITIONAL([ENABLE_GCOV], [test x$enable_gcov = xyes])
AC_SUBST(ENABLE_GCOV)

if test x$enable_gcov = xyes ; then
   CFLAGS=`echo "$CFLAGS" | sed 's/-O2/-O0/g'`
fi




# LIBCW_LIBDIR is needed to extend value of LD_LIBRARY_PATH used when starting
# test instance of cwdaemon.
if $PKG_CONFIG --atleast-version=5 libcw; then
   LIBCW_LIBS=`$PKG_CONFIG libcw --libs`
   LIBCW_CFLAGS=`$PKG_CONFIG libcw --cflags`
   LIBCW_LIBDIR=`$PKG_CONFIG libcw --variable=libdir`
else
   AC_MSG_ERROR(Can't find libcw library)
fi
AC_SUBST(LIBCW_LIBS)
AC_SUBST(LIBCW_CFLAGS)
AC_SUBST(LIBCW_LIBDIR)



# On Alpine Linux 3.17 using busybox/gzip, the "--best" option doesn't exit,
# and the "-d" and "-{1-9}" don't mix well.
#
# case 'cwdaemon-0.12.0.tar.gz' in \
#*.tar.gz*) \
#  eval GZIP= gzip --best -dc cwdaemon-0.12.0.tar.gz | ${TAR-tar} xf - ;;\
#*.tar.bz2*) \
#  bzip2 -dc cwdaemon-0.12.0.tar.bz2 | ${TAR-tar} xf - ;;\
# [...[
#esac
#gzip: unrecognized option: best
my_gzip_env="--best"
if gzip --best -d 2>&1 | grep "unrecognized" > /dev/null; then
   my_gzip_env=""
fi
AC_SUBST(GZIP_ENV, $my_gzip_env)




# Makefiles for functional tests are included unconditionally because those
# Makefiles need to be executed for "make dist". Distribution archive needs
# to always include functionality tests, even if "./configure" was executed
# without "--enable-functional-tests".
AC_CONFIG_FILES([Makefile
	src/Makefile
	doc/Makefile
	examples/Makefile
	doc/cwdaemon.8
	cwdaemon.spec
	tests/Makefile
	tests/unit_tests/Makefile
	tests/library/Makefile
	tests/functional_tests/Makefile
	tests/functional_tests/unattended/Makefile
	tests/functional_tests/unattended/option_cwdevice_tty_lines/Makefile
	tests/functional_tests/unattended/option_port/Makefile
	tests/functional_tests/unattended/request_caret/Makefile
	tests/functional_tests/unattended/request_esc_exit/Makefile
	tests/functional_tests/unattended/request_esc_cwdevice/Makefile
	tests/functional_tests/unattended/request_esc_reply/Makefile
	tests/functional_tests/unattended/request_plain/Makefile
	tests/functional_tests/unattended/reset_register_callback/Makefile
	tests/functional_tests/supervised/Makefile
	tests/functional_tests/supervised/feature_multiple_requests/Makefile
	tests/functional_tests/supervised/request_esc_sound_system/Makefile
	tests/fuzzing/Makefile
	tests/fuzzing/simple/Makefile
	])

AC_OUTPUT




# Put this at the very end, so that these are the last lines seen by user on
# console.
AC_MSG_NOTICE([----------------------------------------------------------])
AC_MSG_NOTICE([---------- $PACKAGE_NAME $PACKAGE_VERSION build configuration -----------])
AC_MSG_NOTICE([  operating system: .....................  $host_os])
AC_MSG_NOTICE([  libcw library path: ...................  $LIBCW_LIBDIR])
AC_MSG_NOTICE([  libcw library version: ................  $(pkg-config --modversion libcw)])
AC_MSG_NOTICE([  LIBCW_LIBS: ...........................  $LIBCW_LIBS])
AC_MSG_NOTICE([  LIBCW_CFLAGS: .........................  $LIBCW_CFLAGS])
AC_MSG_NOTICE([  CFLAGS: ...............................  $CFLAGS])
AC_MSG_NOTICE([  enable unit tests: ....................  yes])
AC_MSG_NOTICE([  enable gcov: ..........................  $enable_gcov])
AC_MSG_NOTICE([  enable functional tests: ..............  $enable_functional_tests])
if test x$enable_functional_tests = xyes ; then
    AC_MSG_NOTICE([      run long functional tests: ........  $enable_long_functional_tests])
    AC_MSG_NOTICE([      test tty cwdevice name: ...........  $tests_tty_cwdevice_name])
    AC_MSG_NOTICE([      path to cwdaemon binary: ..........  $tests_cwdaemon_path])
fi
AC_MSG_NOTICE([----------------------------------------------------------])
