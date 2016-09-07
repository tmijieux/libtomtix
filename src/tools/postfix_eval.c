#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tomtix/stack.h"

static void die(const char *str, ...)
{
    va_list vl;
    va_start(vl, str);
    vfprintf(stderr, str, vl);
    exit(EXIT_FAILURE);
}

// this program is a postfix 1-digit calculator
int main(int argc, char *argv[])
{
    int c;
    struct stack s;
    char op1, op2, res;
	
    stack_init(&s);
    c = getchar();
    while (c != '\n') {
        if (c >= '0' && c <= '9') {
            stack_push(&s, c);
        } else if (c == '+' ||
                   c == '-' ||
                   c == '*') {
            op2 = stack_pop(&s);
            op1 = stack_pop(&s);
            switch (c) {
            case '+':
                res = op1 + op2 - '0';
                break;
            case '-':
                res = op1 - op2 + '0';
                break;
            case '*':
                res = (op1 - '0') * (op2 - '0') + '0';
                break;
            default:
                break;
            }
            stack_push(&s, res);
        }  else
            die("error: invalid character\n");
        c = getchar();
    }
    c = stack_pop(&s);
    if (c >= '0' && c <= '9') {
        putchar(c);
        puts("");
    } else if (c >= '0' - 9 && c < '0') {
        putchar('-');
        putchar(2*'0' - c);
        puts("");
    } else {
        puts("overflow");
    }
    return EXIT_SUCCESS;
}
