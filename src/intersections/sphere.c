//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

double	hit_sphere(const t_sphere *sphere, t_ray r)
{
	double radius = sphere->diameter / 2;
	double b = 2 * dot(r.direction, min_vec(r.origin, sphere->coordinates));
	double len = len3(min_vec(r.origin, sphere->coordinates));
	double c = (len * len) - (radius * radius);
	double delta = b * b - 4 * c;
	if (delta > 0)
	{
		double t1 = (-b + sqrt(delta)) / 2;
		double t2 = (-b - sqrt(delta)) / 2;
		if (t1 > 0 && t2 > 0)
		{
			if (t1 < t2)
				return (t1);
			return (t2);
		}
	}
	return (-1);
}
