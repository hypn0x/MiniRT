#include <types.h>
#include <math.h>

t_vec3	rotate_y_axis(double angle, t_vec3 v)
{
	t_vec3	r;

	r.x = v.x * cos(angle) + v.z * sin(angle);
	r.y = v.y;
	r.z = -v.x * sin(angle) + v.z * cos(angle);
	return (r);
}

t_vec3	rotate_x_axis(double angle, t_vec3 v)
{
	t_vec3	r;

	r.x = v.x;
	r.y = v.y * cos(angle) - v.z * sin(angle);
	r.z = v.y * sin(angle) + v.z * cos(angle);
	return (r);
}
