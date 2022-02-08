//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

double hit_plane(t_plane *plane, t_ray r)
{
	double dn_dot;
	double t;
	t_vec3 normal;
	t_vec3 tmp;
	normal = (plane->orientation);
	dn_dot = dot(r.direction, normal);
	if (fabs(dn_dot) > 1e-6)
	{
		tmp = min_vec(r.direction, normal);
		t = dot(tmp, normal) / dn_dot;
		return (t);
	}
	return (-1);
}
