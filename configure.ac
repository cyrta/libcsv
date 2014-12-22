
# inspired by:
## https://raw.githubusercontent.com/nanomsg/nanomsg/master/configure.ac
## http://mij.oltrelinux.com/devel/autoconf-automake/
## http://www.linuxselfhelp.com/gnu/autoconf/html_chapter/autoconf_3.html


##Autoconf requirements
## 	AC_INIT(package, version, bug-report-address)
## 	information on the package
## 	checks for programs
## 	checks for libraries
## 	checks for header files
## 	checks for types
## 	checks for structures
## 	checks for compiler characteristics
## 	checks for library functions
## 	checks for system services
## 	AC_CONFIG_FILES([file...])
## 	AC_OUTPUT



AC_PREREQ([2.53])

#AC_INIT(package, version, bug-report-address)
AC_INIT(libcsv, 0.1)

#AC_INIT([nanomsg], [m4_esyscmd([./package_version.sh])],
#   [nanomsg@freelists.org], [nanomsg], [http://nanomsg.org/])
   
AC_CONFIG_SRCDIR([src/csv.h])
AM_INIT_AUTOMAKE([1.6 foreign subdir-objects tar-ustar dist-zip])
m4_ifdef([AM_SILENT_RULES],
    [AM_SILENT_RULES([yes])
])

AC_CANONICAL_HOST
 
################################################################################
#  Check the compilers.                                                         #
################################################################################

AC_PROG_CC_C99
AM_PROG_CC_C_O


################################################################################
#  Check whether GCC compiler is used.                                         #
################################################################################
AS_IF([test x"$GCC" = xyes],
    [AC_DEFINE([NN_HAVE_GCC])]
)

################################################################################
#  Check whether ICC compiler is used.                                         #
################################################################################
AC_CACHE_CHECK([whether we are using ICC compiler],
    [ac_cv_icc_compiler],
    [AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([], [[
            #ifndef __INTEL_COMPILER
               #error
            #endif
            ]])],
        [ac_icc_compiler=yes],
        [ac_icc_compiler=no])
    ac_cv_icc_compiler=$ac_icc_compiler])
AS_IF([test x"$ac_cv_icc_compiler" = xyes],
    [AC_DEFINE([NN_HAVE_ICC])]
)

################################################################################
#  Check whether Sun Studio compiler is used.                                  #
################################################################################
AC_CACHE_CHECK([whether we are using Sun Studio compiler],
    [ac_cv_sun_studio_compiler],
    [AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([], [[
            #ifndef __SUNPRO_C
                #error
            #endif
            ]])],
        [ac_sun_studio_compiler=yes],
        [ac_sun_studio_compiler=no])
    ac_cv_sun_studio_compiler=$ac_sun_studio_compiler])
AS_IF([test x"$ac_cv_sun_studio_compiler" = xyes],
    [AC_DEFINE([NN_HAVE_SUN_STUDIO])]
)

################################################################################
#  Check whether clang compiler is used.                                       #
################################################################################
AC_CACHE_CHECK([whether we are using clang compiler],
    [ac_cv_clang_compiler],
    [AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([], [[
            #ifndef __clang__
                #error
            #endif
            ]])],
        [ac_clang_compiler=yes],
        [ac_clang_compiler=no])
    ac_cv_clang_compiler=$ac_clang_compiler])
AS_IF([test x"$ac_cv_clang_compiler" = xyes],
    [AC_DEFINE([NN_HAVE_CLANG])]
)

################################################################################
#  Check whether HP aCC compiler is used.                                      #
################################################################################
AC_CACHE_CHECK([whether we are using HP aCC compiler],
    [ac_cv_hpacc_compiler],
    [AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([], [[
            #ifndef __HP_cc
                #error
            #endif
            ]])],
        [ac_hpacc_compiler=yes],
        [ac_hpacc_compiler=no])
    ac_cv_hpacc_compiler=$ac_hpacc_compiler])
AS_IF([test x"$ac_cv_hpacc_compiler" = xyes],
    [AC_DEFINE([NN_HAVE_HPACC])]
)



################################################################################
#  If --enable-debug is specified set appropriate compiler options.            #
################################################################################

AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug],
    [Enable debugging information [default=no]])])

if test "x$enable_debug" = "xyes"; then
    if test "x$GCC" = "xyes" -o \
            "x$ac_cv_icc_compiler" = "xyes" -o \
            "x$ac_cv_clang_compiler" = "xyes"; then
        CFLAGS="-g -O0 "
    elif test "x$ac_cv_sun_studio_compiler" = "xyes"; then
        CFLAGS="-g0 "
    elif test "x$ac_cv_hpacc_compiler" = "xyes"; then
        CFLAGS="-g +O0 "
    fi
    ORIG_CFLAGS="${CFLAGS:-none}"
    if test "x$ORIG_CFLAGS" != "xnone"; then
        CFLAGS="${CFLAGS} ${ORIG_CFLAGS}"
    fi
    AC_DEFINE([NN_DEBUG])
fi


################################################################################
#  Check which OS we are building for.                                         #
################################################################################

AS_CASE([${host_os}],
    [*linux*],   [AC_DEFINE([NN_HAVE_LINUX])],
    [*mingw32*], [
        AC_DEFINE([NN_HAVE_WINDOWS])
        AC_DEFINE([NN_HAVE_MINGW])
        AC_DEFINE([_WIN32_WINNT],0x0600)
        LIBS="$LIBS -lws2_32 -lMswsock"
    ],
    [*darwin*],  [AC_DEFINE([NN_HAVE_OSX])],
    [*freebsd*], [AC_DEFINE([NN_HAVE_FREEBSD])],
    [*netbsd*],  [AC_DEFINE([NN_HAVE_NETBSD])],
    [*openbsd*], [AC_DEFINE([NN_HAVE_OPENBSD])],
    [*hpux*],    [AC_DEFINE([NN_HAVE_HPUX])],
    [*solaris*], [
        AC_DEFINE([NN_HAVE_SOLARIS])
        AC_CHECK_LIB([socket], [socket])
        AC_CHECK_LIB([nsl], [gethostbyname])
    ],
    [*nto-qnx*], [
        AC_DEFINE([NN_HAVE_QNX])
        AC_CHECK_LIB([socket], [socket])
    ]
)

################################################################################
#  Feature checks.                                                             #
################################################################################

AC_CHECK_HEADERS([stdint.h], [AC_DEFINE([NN_HAVE_STDINT])])

AX_PTHREAD([
  LIBS="$PTHREAD_LIBS $LIBS"
  CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
  CC="$PTHREAD_CC"
])


################################################################################
#  Finish the configuration phase.                                             #
################################################################################

AC_CONFIG_MACRO_DIR([m4])

AC_OUTPUT([
Makefile
libcsv.pc
])


