//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

/* useful equation cheat sheet:
Standard line eq:
𝑎 𝑥 + 𝑏 𝑦 + 𝑐 = 0
The equation of the line can also be realized as a dot product of two vectors as
Standard eq plane :
 𝑎 𝑥 + 𝑏 𝑦 + 𝑐 𝑧 + 𝑑 = 0
Plane from 2 points:
𝑎 ( 𝑥 − 𝑥 ) + 𝑏 ( 𝑦 − 𝑦 ) + 𝑐 ( 𝑧 − 𝑧 ) = 0
Normal vector on olane given two vects on point:
cross_p
ray_plane intersections:
point in plane: (p−p0)⋅n=0
ray : l0+l∗t=p
two eqs in one : (l0+l∗t−p0)⋅n=0
compute t:
t = =−(l0−p0)⋅n/ l⋅n
- l0 is the origin of the ray
-  l is the ray direction
- p0 point far away in plane
- n normm vec
*/

//bool intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, float &t)
//{
//// assuming vectors are all normalized
//float denom = dotProduct(n, l);
//if (denom > 1e-6) {
//Vec3f p0l0 = p0 - l0;
//t = dotProduct(p0l0, n) / denom;
//return (t >= 0);
//}
//
//return false;
//}

float hit_plane(t_plane *plane, t_ray r)
{
	float dn_dot;
	float t;

	dn_dot = dot(plane->orientation, r.direction);
	if (fabsf(dn_dot) > 1e-6)
	{
		t_vec3 p0l0 = min_vec(plane->coordinates, r.origin);
		t = dot(p0l0, plane->orientation) / dn_dot;
		if (fabsf(t) > 0)
			return (t);
	}
	return (-1);
}
