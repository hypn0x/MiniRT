//
// Created by segransm on 1/26/22.
//
#include <types.h>

t_vec3	mult3(t_vec3 a, double n)
{
	a.x *= n;
	a.y *= n;
	a.z *= n;
	return (a);
}

t_vec3	div3(t_vec3 a, double n)
{
	a.x /= n;
	a.y /= n;
	a.z /= n;
	return (a);
}

t_vec3	plus3(t_vec3 a, double n)
{
	a.x += n;
	a.y += n;
	a.z += n;
	return (a);
}

t_vec3	min3(t_vec3 a, double n)
{
	a.x -= n;
	a.y -= n;
	a.z -= n;
	return (a);
}
