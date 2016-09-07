AC_INIT([libtomtix], [0.1], [tmijieux@ipb.fr])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])

### TOOLS ##

AC_PROG_CC
AM_PROG_AR
PKG_PROG_PKG_CONFIG
LT_INIT([])

### LIBRARIES ##

PKG_CHECK_MODULES([YAML], [yaml-0.1])
PKG_CHECK_MODULES([LZMA], [liblzma])
PKG_CHECK_MODULES([PYTHON2], [python2])
PKG_CHECK_MODULES([CRYPTO], [libcrypto])
PKG_CHECK_MODULES([GLIB], [glib-2.0])

###  ##


### OUTPUT ##
AC_CONFIG_FILES([
		  Makefile
		  src/Makefile
		  src/lib/Makefile
		  src/tools/Makefile
               ])
AC_OUTPUT
