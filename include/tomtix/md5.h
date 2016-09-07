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

#ifndef t_MD5_H
#define t_MD5_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <openssl/md5.h>

int t_md5_hash_file(FILE *f, char **md5_hash_str);
int t_md5_hash_buf(size_t size, uint8_t const *buf, uint8_t *md5_hash);

#endif // t_MD5_H
