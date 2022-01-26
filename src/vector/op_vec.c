//
// Created by segransm on 1/26/22.
//
#include <types.h>
#include <math.h>
#include <op_vec_double.h>

t_vec3 min_vec(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3	plus_vec(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

double	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double len3(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3 unit_vector(t_vec3 a)
{
	return (div3(a, len3(a)));
}
