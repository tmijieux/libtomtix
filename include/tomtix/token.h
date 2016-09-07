/*
  Copyright (C) 2016 Thomas Mijieux

  This file is part of libtomtix.

  libtomtix is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  libtomtix is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef t_TOKEN_H
#define t_TOKEN_H

#include <stdbool.h>

typedef enum t_token_type {
    T_TOKEN_OPENING_PAREN,
    T_TOKEN_CLOSING_PAREN,
    T_TOKEN_OPERATOR,
    T_TOKEN_INTEGER,
    T_TOKEN_DOUBLE,
    T_TOKEN_CHAR,
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
