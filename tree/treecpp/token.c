#include "token.h"

int token_is_value(struct token *tok)
{
	return (tok->type == INTEGER || tok->type == DOUBLE);
}

int token_is_operator(struct token *tok)
{
	return tok->type == OPERATOR;
}

int token_is_closing_paren(struct token *tok)
{
	return tok->type == CLOSING_PAREN;
}
