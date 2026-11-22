AC_PREREQ([2.72])
AC_INIT([enginepipe], [1.5], [pmorales23@alumnos.utalca.cl])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_PATH_PROG([NVCC], [nvcc])
AS_IF([test -z "$NVCC"], [AC_MSG_ERROR([nvcc no encontrado: instale el CUDA Toolkit y agregue su bin al PATH])])
CUDA_LIBDIR="$(dirname "$(dirname "$NVCC")")/lib64"
AC_SUBST([CUDA_LIBDIR])
AC_ARG_VAR([NVCC_ARCH], [native])
AS_IF([test -z "$NVCC_ARCH"], [NVCC_ARCH=native])
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
NVCC_CCBIN="$CXX"
AC_SUBST([NVCC_CCBIN])
AX_CXX_COMPILE_STDCXX([20], [noext], [mandatory])
LT_INIT([disable-static])
AC_LANG_PUSH([C++])
AC_OPENMP
AC_LANG_POP([C++])
AX_PTHREAD
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT