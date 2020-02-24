
AC_PREREQ([2.61])
AC_INIT([gsplugin-customcategories], [1.0], [erico.mendonca@suse.com])
AC_CONFIG_AUX_DIR(aux-dist)
AM_INIT_AUTOMAKE

AC_PROG_MAKE_SET
AC_PROG_CXX
AC_LANG(C++)

CXXFLAGS="-Wall -fPIC"

AC_CONFIG_MACRO_DIR([m4])

LT_PREREQ([2.2])
LT_INIT([dlopen shared])

AC_CONFIG_FILES([Makefile include/Makefile src/Makefile])

PKG_CHECK_MODULES([GS], [gnome-software], [], [AC_MSG_ERROR([Please install gnome-software-devel!])])
AC_SUBST(libdir, [[$(pkg-config gnome-software --variable=plugindir)]])
AC_OUTPUT

