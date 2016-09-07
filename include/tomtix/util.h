#ifndef TOMTIX_UTIL_H
#define TOMTIX_UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef void (*t_freefun)(void*);

#define HANDLE_ARRAY_SIZE(array, array_size, array_capacity)            \
    do {                                                                \
        if (array_size+1 > array_capacity) {                            \
            array_capacity = 2*(array_capacity)+1;                      \
            g_assert(array_capacity > array_size);                      \
            array = g_realloc(array, sizeof(*(array)) * array_capacity); \
        }                                                               \
    } while (0)                                                         \

#define ALLOC_ARRAY(array_var, size_var, size)                  \
    do {                                                        \
        array_var = g_malloc((size) * sizeof(*(array_var)));    \
        size_var = (size);                                      \
    } while (0)

#define ARRAY_DUP(array_var, size)                              \
    (g_memdup((array_var), (size) * sizeof(*(array_var))))

#define COPY_ARRAY(array_dst_var, array_src_var, size)                  \
    memcpy((array_dst_var), (array_src_var), (size) * sizeof(*(array_dst_var)))

#define ARRAY_SIZE(array) (sizeof (array) / sizeof((array)[0]))
#define OFFSET_OF(type, field) ((int)(uintptr_t)(&((type*)0)->field))
#define SWAP_POINTER(X, Y, TMP) do { (TMP) = (X); (X) = (Y); (Y)=(TMP);}while(0)

#ifdef MIN
#undef MIN
#endif
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#ifdef MAX
#undef MAX
#endif
#define MAX(x, y) ((x) < (y) ? (y) : (x))
#define SQUARE(x) ((x)*(x))

// GIOChannel *t_open_text_file_reading(char const *file_path);
// int t_getline(GIOChannel *chan, char **return_value);

char *t_bytearray2hexstr(uint8_t const *bytearray, size_t size);
char *t_get_file_hashstr(char const *file_path);
unsigned t_strsplit_size(char **split);


void* t_memdup(void *buf, size_t size);
    
#endif // TOMTIX_UTIL_H
