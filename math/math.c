#define __USE_XOPEN 1

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <utils/math.h>
#include <utils/vec.h>
/**
 * @file math.c
 */

/**
 * Normaliser un vecteur.
 * @param v - Vecteur à normaliser (modifié).
 */
void vec3_normalize(vec3 *v)
{
	double n = sqrt(v->x*v->x+v->y*v->y+v->z*v->z);
	v->x /= n;  v->y /= n;  v->z /= n;
}

/**
 * Convertion radian -> degrée.
 * @param radian - Angle en radian.
 * @return int - Angle en degrée.
 */
int radian_to_degree(double radian)
{
	return (int) (radian * 180. / M_PI);
}

/**
 * Convertion degrée -> radian.
 * @param degree - Angle en degrée.
 * @return double - Angle en radian.
 */
double degree_to_radian(int degree)
{
	return (double) degree * M_PI / 180.;
}

/**
 * Obtenir l'angle en degrée décrit par un vecteur.
 * @param src - Source du vecteur.
 * @param dst - Destination du vecteur.
 * @return double - Angle en degrée.
 */
double angle_rotation_pingouin(const vec3 *src, const vec3 *dst)
{
	vec3 a = { dst->x-src->x, 0., dst->z-src->z };
	if (a.x == 0. && a.z == 0.)
		return 400.;
	vec3_normalize(&a);  double s = -a.x;
	return radian_to_degree( (s < 0 ? 1. : -1.) * acos(a.z));
}

/**
 * Obtenir la matrice de rotation décrite par une position et un angle.
 * @param ax - Position d'un point.
 * @param angle - Angle de rotation.
 * @return double * - Matrice de rotation.
 */
double *rotation_matrix(vec3 ax, double angle)
{
	double co = cos(angle), co2 = 1.-co, si = sin(angle);
	double xx = ax.x*ax.x, yy = ax.y*ax.y, zz = ax.z*ax.z;
	double xy = ax.x*ax.y, xz = ax.x*ax.z, yz = ax.y*ax.z; 
	double r[9] = {
		co+xx*co2, xy*co2-ax.z*si, xz*co2+ax.y*si,
		xy*co2+ax.z*si, co+yy*co2, yz*co2-ax.x*si,
		xz*co2-ax.y*si, yz*co2+ax.x*si, co+zz*co2
	};
	double *rot = malloc(9 * sizeof(*rot));
	memcpy(rot, r, 9 * sizeof(*rot));
	return rot;
}

/**
 * Multiplier un vec3 par une matrice.
 * @param P - vec3 à multiplier (modifié).
 * @param mat - Matrice.
 */
void matrix_multiply(vec3 *P, double mat[9])
{
	vec3 p = *P;
	P->x = mat[0]*p.x + mat[1]*p.y+mat[2]*p.z;
	P->y = mat[3]*p.x + mat[4]*p.y+mat[5]*p.z;
	P->z = mat[6]*p.x + mat[7]*p.y+mat[8]*p.z;
}
