#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "string2.h"

#define HEURISTIC_SIZE 64

char *xvasprintf(const char *format, va_list ap)
{
    va_list cpy;
    char *buf = malloc(sizeof(*buf) * HEURISTIC_SIZE);
    va_copy(cpy, ap);

    int n = vsnprintf(buf, HEURISTIC_SIZE, format, ap);
    if (n >= HEURISTIC_SIZE) {
	buf = realloc(buf, n + 1);
	vsnprintf(buf, n + 1, format, cpy);
    }
    va_end(cpy);
    return buf;
}

char *xasprintf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    char *res = xvasprintf(format, ap);
    va_end(ap);
    return res;
}

char *string_replace_char(const char *str, char from, char to)
{
    char *rep = strdup(str);
    for (int i = 0; rep[i] != '\0'; ++i)
	if (rep[i] == from)
	    rep[i] = to;
    return rep;
}

char *strstrip(const char *str)
{
    char *strip_ = strdup(str);
    strstripc(strip_, '\n');
    return strip_;
}

uint32_t string_split(const char *str, const char *delim, char ***buf_addr)
{
    if (NULL == str) {
        *buf_addr = NULL;
        return 0;
    }

    char *strw = strdup(str);
    struct list *li = list_new(0);
    char *saveptr;
    char *p =  strtok_r(strw, delim, &saveptr);
    while (p != NULL) {
	list_add(li, strdup(p));
	p = strtok_r(NULL, delim, &saveptr);
    }
    free(strw);

    unsigned int s = list_size(li);
    if (!s) {
	*buf_addr = NULL;
    } else {
	*buf_addr = malloc(sizeof(*buf_addr) * s);
        for (unsigned i = 1; i <= s; ++i)
            (*buf_addr)[s - i] = list_get(li, i);
    }
    list_free(li);
    return s;
}

uint32_t string_split2(const char *str, const char *delim, char ***buf_addr)
{

    if (NULL == str) {
        *buf_addr = NULL;
        return 0;
    }

    struct list *li = list_new(0);
    int delim_length = strlen(delim);
    const char *str_ptr1, *str_ptr2;

    str_ptr1 = str;
    while (NULL != (str_ptr2 = strstr(str_ptr1, delim))) {
	list_add(li, strndup(str_ptr1, str_ptr2 - str_ptr1));
        str_ptr1 = str_ptr2 + delim_length;
    }
    list_add(li, strdup(str_ptr1));

    unsigned int s = list_size(li);
    if (!s) {
	*buf_addr = NULL;
    } else {
	*buf_addr = malloc(sizeof(*buf_addr) * s);
        for (unsigned i = 1; i <= s; ++i)
            (*buf_addr)[s - i] = list_get(li, i);
    }
    list_free(li);
    return s;
}

int string_have_extension(const char *filename, const char *extension)
{
    size_t l = strlen(filename);
    size_t e = strlen(extension);
    if (l < e)
        return false;
    return !strcmp(extension, filename + l - e);
}
