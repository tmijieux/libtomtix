pkgconfdir=$(sysconfdir)/$(PACKAGE)
AM_CFLAGS = \
	-Wall -Wextra \
	-std=gnu99

AM_CPPFLAGS = \
	-I$(top_srcdir)/include

AM_LDFLAGS = \
	-no-undefined
