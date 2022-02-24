/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:32:52 by                   #+#    #+#             */
/*   Updated: 2022/02/24 12:03:30 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hit_objs.h>
#include <op_vec.h>
#include <op_vec_double.h>
#include <math.h>

int	solve_quadratic(t_vec3 vec, float *x0, float *x1)
{
	float	discr;
	float	q;

	discr = powf(vec.y, 2) - 4 * vec.x * vec.z;
	if (discr < 0)
		return (-1);
	if (discr == 0)
	{
		*x0 = -0.5f * vec.y / vec.x;
		*x1 = -0.5f * vec.y / vec.x;
	}
	else
	{
		if (vec.y > 0)
			q = -(vec.y + sqrtf(discr)) / 2;
		else
			q = -(vec.y - sqrtf(discr)) / 2;
		*x0 = q / vec.x;
		*x1 = vec.z / q;
	}
	return (0);
}

int	cylinder_root(float *t0, float *t1, t_cylinder *cylinder, t_ray ray)
{
	t_vec3	a_sqrt;
	t_vec3	right;
	float	x;
	float	y;
	float	z;

	a_sqrt = min_vec(ray.direction,
			mult3(cylinder->orientation,
				dot(ray.direction, cylinder->orientation)));
	x = dot(a_sqrt, a_sqrt);
	right = min_vec(min_vec(ray.origin, cylinder->coordinates),
			mult3(cylinder->orientation,
				dot(min_vec(ray.origin, cylinder->coordinates),
					cylinder->orientation)));
	y = 2 * dot(a_sqrt, right);
	z = dot(right, right) - (cylinder->diameter / 2 * cylinder->diameter / 2);
	if (solve_quadratic(new_vec(x, y, z), t0, t1))
		return (0);
	return (1);
}

float	hit_cylinder(t_cylinder *cylinder, t_ray ray)
{
	float	t0;
	float	t1;

	if (cylinder->diameter > 2 && cylinder->orientation.z == 1)
		cylinder->diameter = 2;
	create_caps(cylinder);
	if (!cylinder_root(&t0, &t1, cylinder, ray))
		return (-1);
	check_t(&t0, cylinder, ray);
	check_t(&t1, cylinder, ray);
	if (t0 < 0 && t1 < 0)
		return (-1);
	if (t1 < t0)
	{
		if (t1 >= 0)
			return (t1);
		else
			return (t0);
	}
	else
	{
		if (t0 > 0)
			return (t0);
		else
			return (t1);
	}
}
