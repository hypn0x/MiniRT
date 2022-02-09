//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

float	hit_sphere(const t_sphere *sphere, t_ray r)
{
	float radius = sphere->diameter / 2;
	float b = 2 * dot(r.direction, min_vec(r.origin, sphere->coordinates));
	float len = len3(min_vec(r.origin, sphere->coordinates));
	float c = (len * len) - (radius * radius);
	float delta = b * b - 4 * c;
	if (delta >= 0)
	{
		float t1 = (-b + sqrtf(delta)) / 2;
		float t2 = (-b - sqrtf(delta)) / 2;
		if (t1 > 0 && t2 > 0)
		{
			if (t1 < t2)
				return (t1);
			return (t2);
		}
	}
	return (-1);
}
