#ifndef STRING2_H
#define STRING2_H

#include <stdint.h>
#include <stdarg.h>

char *xasprintf(const char *format, ...);
char *xvasprintf(const char *format, va_list ap);
uint32_t string_split2(const char *str, const char *delim, char ***buf_addr);
uint32_t string_split(const char *str, const char *delim, char ***buf_addr);
int string_have_extension(const char *filename, const char *extension);

#endif //STRING2_H
