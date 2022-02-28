/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:32:06 by                   #+#    #+#             */
/*   Updated: 2022/02/28 18:35:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

//TODO: Fast, minimum storage ray-triangle intersection - Möller-Trumbore

static int	solve_quadratic(t_triangle *triangle, t_vec3 P, t_vec3 N)
{
	t_vec3	c;
	t_vec3	edge;
	t_vec3	v;

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

// e01 edges

float	hit_triangle(t_triangle *triangle, t_ray ray)
{
	t_vec3	e01[2];
	t_vec3	normal;
	t_vec3	point;
	float	edge;
	float	t;

	e01[0] = min_vec(triangle->b, triangle->a);
	e01[1] = min_vec(triangle->c, triangle->a);
	normal = normalize(cross_prod(e01[0], e01[1]));
	edge = dot(normal, ray.direction);
	if (isless(fabsf(edge), (float)1e-6))
		return (-1);
	t = dot(normal, min_vec(triangle->a, ray.origin)) / edge;
	if (isless(t, 0))
		return (-1);
	point = plus_vec(ray.origin, mult3(ray.direction, t));
	if (solve_quadratic(triangle, point, normal))
		return (t);
	return (-1);
}
