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

#include "tomtix/token.h"

bool t_token_is_value(t_token *tok)
{
    return (tok->type == T_TOKEN_INTEGER || tok->type == T_TOKEN_DOUBLE);
}

bool t_token_is_operator(t_token *tok)
{
    return tok->type == T_TOKEN_OPERATOR;
}

bool t_token_is_closing_paren(t_token *tok)
{
    return tok->type == T_TOKEN_CLOSING_PAREN;
}
