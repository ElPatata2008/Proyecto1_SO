AC_PREREQ([1.0])
AC_INIT([renpipe], [1.0], [pmorales23@alumnos.utalca.cl])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([20], [noext], [mandatory])
LT_INIT
AC_OPENMP
AX_PTHREAD
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT