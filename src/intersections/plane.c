//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

float hit_plane(t_plane *plane, t_ray r)
{
	float dn_dot;
	float t;

	dn_dot = dot(plane->orientation, r.direction);
	if (islessgreater(dn_dot, 1e-6f))
	{
		t_vec3 p0l0 = min_vec(plane->coordinates, r.origin);
		t = dot(p0l0, plane->orientation) / dn_dot;
		if (t > 0)
			return (t);
	}
	return (-1);
}
