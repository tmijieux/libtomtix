#ifndef t_TOKEN_H
#define t_TOKEN_H

#include <stdbool.h>

typedef enum t_token_type {
    TX_TOKEN_OPENING_PAREN,
    TX_TOKEN_CLOSING_PAREN,
    TX_TOKEN_OPERATOR,
    TX_TOKEN_INTEGER,
    TX_TOKEN_DOUBLE,
    TX_TOKEN_CHAR,
} t_token_type;

typedef struct t_token_ t_token;
struct t_token_ {
    int type;
    union {
        char c;
        long l;
        double d;
    };
};

bool t_token_is_value(t_token *tok);
bool t_token_is_operator(t_token *tok);
bool t_token_is_closing_paren(t_token *tok);

#endif //TOKEN_H
