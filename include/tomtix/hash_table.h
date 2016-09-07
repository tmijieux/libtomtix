#ifndef t_HASH_TABLE_H
#define t_HASH_TABLE_H

/*
 * This file is part of libtomtix
 *
 *  Copyright (©)  Thomas Mijieux
 *
 * libtomtix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libtomtix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

typedef struct t_hashtable_ t_hashtable;
#include "tomtix/util.h"
#include "tomtix/list.h"

t_hashtable *t_hashtable_new(size_t size);
t_hashtable *t_hashtable_new_full(size_t size, t_freefun free);
unsigned t_hashtable_size(t_hashtable const *h);
int t_hashtable_insert(t_hashtable* ht, char const *key, void *data);
int t_hashtable_lookup(
    t_hashtable *ht, char const *lookup_key, void *ret_value);

int t_hashtable_add(t_hashtable* ht, char const *key);
int t_hashtable_contains(t_hashtable *ht, char const *key);

int t_hashtable_remove(t_hashtable *ht, char const *key);

void t_hashtable_foreach(
    t_hashtable* ht, 
    void (*fun)(char const *key, void *value, void *user_data), // callback
    void *user_data // data to be passed to the callback
);

t_list* t_hashtable_to_list(t_hashtable *h);
void t_hashtable_delete(t_hashtable *ht);

#endif // t_HASH_TABLE_H
