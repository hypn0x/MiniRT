#include <types.h>
#include <math.h>

t_vec3	rotate_y_axis(float angle, t_vec3 v)
{
	t_vec3	r;

	r.x = v.x * cosf(angle) + v.z * sinf(angle);
	r.y = v.y;
	r.z = -v.x * sinf(angle) + v.z * cosf(angle);
	return (r);
}

t_vec3	rotate_x_axis(float angle, t_vec3 v)
{
	t_vec3	r;

	r.x = v.x;
	r.y = v.y * cosf(angle) - v.z * sinf(angle);
	r.z = v.y * sinf(angle) + v.z * cosf(angle);
	return (r);
}
