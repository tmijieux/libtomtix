#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stack.h"

static void die(const char *str, ...)
{
	va_list vl;
	va_start(vl, str);
	vfprintf(stderr, str, vl);
	exit(EXIT_FAILURE);
}

// this program convert bracketed infix to postfix
int main(int argc, char *argv[])
{
	int c;
	struct stack s;

	stack_init(&s);
	c = getchar();
	while (c != '\n') {
		if (c == '(' ||
		    c == '+' ||
		    c == '-' ||
		    c == '*') {
			stack_push(&s, (char)c);
		} else if ((c >= 'a' && c <= 'z') ||
			   (c >= '0' && c <= '9')) {
			putchar(c);
		} else if (c == ')') {
			char tmp;
			while ((tmp = stack_pop(&s)) != '(') {
				putchar(tmp);
			}
		} else {
			die("erreur: caractère non autorisé\n");
		}
		c = getchar();
	}
	puts(""); // LF
	return EXIT_SUCCESS;
}
