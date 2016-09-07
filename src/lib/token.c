#include "tomtix/token.h"

bool t_token_is_value(t_token *tok)
{
    return (tok->type == TX_TOKEN_INTEGER || tok->type == TX_TOKEN_DOUBLE);
}

bool t_token_is_operator(t_token *tok)
{
    return tok->type == TX_TOKEN_OPERATOR;
}

bool t_token_is_closing_paren(t_token *tok)
{
    return tok->type == TX_TOKEN_CLOSING_PAREN;
}
