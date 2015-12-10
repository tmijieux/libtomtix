#ifndef TOKEN_H
#define TOKEN_H

enum {
	OPENING_PAREN,
	CLOSING_PAREN,
	OPERATOR,
	INTEGER,
	DOUBLE,
	CHAR
};

struct token {
	int type;
	union {
		char c;
		long l;
		double d;
	} u;
};

int token_is_value(struct token *tok);
int token_is_operator(struct token *tok);
int token_is_closing_paren(struct token *tok);

#endif //TOKEN_H
