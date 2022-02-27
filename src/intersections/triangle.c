//
// Created by Hajar Sabir on 2/26/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <op_vec_double.h>
#include <math.h>

//TODO: Fast, minimum storage ray-triangle intersection - Möller-Trumbore

static int	solve_quadratic(t_triangle *triangle, t_vec3 P, t_vec3 N)
{
	t_vec3 	c;
	t_vec3 	edge;
	t_vec3 	v;

	edge = min_vec(triangle->b, triangle->a);
	v = min_vec(P, triangle->a);
	c = cross_prod(edge, v);
	if (isless(dot(N, c), 0))
		return (0);
	edge = min_vec(triangle->c, triangle->b);
	v = min_vec(P, triangle->b);
	c = cross_prod(edge, v);
	if (isless(dot(N, c), 0))
		return (0);
	edge = min_vec(triangle->a, triangle->c);
	v = min_vec(P, triangle->c);
	c = cross_prod(edge, v);
	if (isless(dot(N, c), 0))
		return (0);
	return (1);
}

float	hit_triangle(t_triangle *triangle, t_ray ray)
{
	t_vec3	A; // edge0
	t_vec3	B; // edge1
	t_vec3	N;  // Triangle normal
	t_vec3	P;
	float	edge;
	float	t;

	A = min_vec(triangle->b, triangle->a);
	B = min_vec(triangle->c, triangle->a);
	N = normalize(cross_prod(A, B));
	edge = dot(N, ray.direction);
	if (isless(fabsf(edge), (float)1e-6))
		return (-1);
	t = dot(N, min_vec(triangle->a, ray.origin)) / edge;
	if (isless(t, 0))
		return (-1);
	P = plus_vec(ray.origin, mult3(ray.direction, t));
	if (solve_quadratic(triangle, P, N))
		return (t);
	return (-1);
}
