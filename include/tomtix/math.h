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

#ifndef t_MATH_H
#define t_MATH_H

#include <stdbool.h>
#define __USE_XOPEN 1
#include <math.h>

typedef struct vec2 {
    float x, y;
} vec2;

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct vec4 {
    float x, y, z, w;
} vec4;

void t_vec4_diff(vec4 *a, vec4 *b, vec4 *c);
float t_vec4_norm(vec4 *a);
void t_vec3_normalize(vec3 *v);
void t_vec4_normalize(vec4 *a);
void t_vec4_print(vec4 *v);
void t_mat4_print(float *mat);

#define t_deg2rad(deg) (M_PI * (deg) / 180.)
#define t_rad2deg(rad) (180.*(rad)/M_PI)

void t_matrix_rotation(float *out, float angle, vec4 direction);
void t_matrix_translation(float *out, vec3 t);
void t_matrix_scale(float *out, vec3 scale);

void t_matrix_vector_multiply(float *M, vec4 *V);
void t_matrix_multiply(float M1[restrict 16],
                       float M2[restrict 16],
                       float OUT[restrict 16]);

void t_matrix_identity(float *M);
void t_matrix_ortho(float M[],
                    float l/*left*/, float r/*right*/,
                    float b/*bottom*/, float t/*top*/,
                    float n/*near*/, float f/*far*/);
void t_matrix_fov_projection(
    float res[], float fov, float aspect, float near, float far);
void t_matrix_look_at(float *res, vec4 eye, vec4 center, vec4 up);

#ifdef SQUARE
#undef SQUARE
#endif
#define SQUARE(x) ((x)*(x))

#define T_SCALAR_MULT4(V, s)                    \
    do {                                        \
        (V).x *= (s);                           \
        (V).y *= (s);                           \
        (V).z *= (s);                           \
        (V).w *= (s);                           \
    } while (0)

#define T_SCALAR_MULT3(V, s)                    \
    do {                                        \
        (V).x *= (s);                           \
        (V).y *= (s);                           \
        (V).z *= (s);                           \
    } while (0)

#define T_ADD4(V, W)                            \
    do {                                        \
        (V).x += (W).x;                         \
        (V).y += (W).y;                         \
        (V).z += (W).z;                         \
        (V).w += (W).w;                         \
    } while (0)

#define T_ADD3(V, W)                            \
    do {                                        \
        (V).x += (W).x;                         \
        (V).y += (W).y;                         \
        (V).z += (W).z;                         \
    } while (0)

#endif // t_MATH_H
