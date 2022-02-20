//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <op_vec_double.h>
#include <math.h>


t_vec3 	vec_unit(t_vec3 vec)
{
	float	len;

	len = sqrtf(len3(vec));
	return (div3(vec, len));
}

t_plane	*create_plane(t_vec3 point, t_vec3 normal, t_colour color)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->coordinates = point;
	pl->orientation = vec_unit(normal);
	pl->colour = color;
	return (pl);
}

float	hit_cap(t_plane *pl, t_ray ray)
{
	t_vec3 	a;
	float		b;
	float		t;

	a = min_vec(pl->coordinates, ray.origin);
	b = dot(pl->orientation, ray.direction);
	t = dot(pl->orientation, a) / b;
	if (t < 0)
		return (-1);
	return (t);
}

float	hit_cylinder_cap(t_cylinder *cy, t_ray ray, float t)
{
	t_vec3 	rt;
	float		h;
	float		tp;
	float		len;
	int			i;

	i = -1;
	while (++i < 2)
	{
		tp = hit_cap(cy->cap[i], ray);
		if (tp != -1 && dot(cy->cap[i]->orientation, ray.direction) <= 0)
		{
			len = len3(min_vec(cy->cap[i]->coordinates,
							   plus_vec(ray.origin, mult3(ray.direction, tp))));
			if (len <= pow(cy->diameter / 2, 2))
				return (tp);
		}
	}
	rt = plus_vec(ray.origin, mult3(ray.direction, t));
	h = dot(min_vec(rt, cy->coordinates), cy->orientation);
	if (0 < h && h < cy->height)
		return (t);
	return (-1);
}

void	check_t(float *t, t_cylinder *cylinder, t_ray ray)
{
	t_vec3	q;
	t_vec3	p2;

	p2 = plus_vec(cylinder->coordinates, mult3(cylinder->orientation, cylinder->height));
	q = plus_vec(ray.origin, mult3(ray.direction, *t));
	if (dot(cylinder->orientation, min_vec(q, cylinder->coordinates)) <= 0)
		*t = (hit_cylinder_cap(cylinder, ray, *t));
	else if (dot(cylinder->orientation, min_vec(q, p2)) >= 0)
		*t = -1;
}

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
//	if (*x0 > *x1)
//		swap_vars(x0, x1);
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
//	t_colour hc;
//	hc.y  = 0;
//	hc.x = 255;
//	hc.z = 0;
	cylinder->cap[0] = create_plane(plus_vec(cylinder->coordinates,
											 mult3(cylinder->orientation, cylinder->height)), cylinder->orientation, cylinder->colour);
	cylinder->cap[1] = create_plane(cylinder->coordinates,
									mult3(cylinder->orientation, -1), cylinder->colour);
	if (!cylinder_root(&t0, &t1, cylinder, ray))
		return (-1);
	if (t0 > 0)
		check_t(&t0, cylinder, ray);
	if (t1 > 0)
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
