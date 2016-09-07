include $(top_srcdir)/common.mk

lib_LTLIBRARIES = libtomtix.la
libtomtix_la_SOURCES = \
	stack.c \
	merge_sort.c \
	partition.c \
	graph.c \
	yaml.c \
	graph_list.c \
	expr2tree.c \
	heap.c \
	tree.c \
	token.c \
	treap.c \
	quick_sort1.c \
	insertion_sort.c \
	graph_utils.c \
	quick_sort2.c \
	md5.c \
	math.c \
	graph_matrix.c

libtomtix_la_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS)
libtomtix_la_CPPFLAGS = $(AM_CPPFLAGS) $(GLIB_CPPFLAGS)
libtomtix_la_LDFLAGS = $(AM_LDFLAGS) $(GLIB_LIBS) $(YAML_LIBS) $(CRYPTO_LIBS) -lm

