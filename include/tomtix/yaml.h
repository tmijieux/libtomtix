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

#ifndef t_YAML_H
#define t_YAML_H

#include <glib.h>

typedef enum t_yaml_type_ {
    T_YAML_LIST,
    T_YAML_TABLE,
    T_YAML_SCALAR,
} t_yaml_type;

typedef struct t_yaml_ {
    t_yaml_type type;
    union {
        GList *list;
        GHashTable *table;
        char *scalar;
        void *value;
    };
} t_yaml;

t_yaml *t_yaml_new_from_file(char const *file_name);
void t_yaml_dump(FILE *out, t_yaml const *yaml);
void t_yaml_free(t_yaml *yaml);

#endif // t_YAML_H
