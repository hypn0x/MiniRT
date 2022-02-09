//
// Created by Hajar Sabir on 2/8/22.
//

#include "../../includes/rendering/colors.h"
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>
#include <math.h>

int	clip_colour(float c)
{
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return ((int)c);
}

int	rgb_to_int(t_colour c)
{
	int	rgb;

	rgb = clip_colour(c.x);
	rgb = (rgb << 8) + clip_colour(c.y);
	rgb = (rgb << 8) + clip_colour(c.z);
	return (rgb);
}

t_colour	get_ray_luminosity(t_data img, t_object obj, t_ray r)
{
	t_colour c = {0, 0, 0};
	t_colour specular = {255, 255, 255};

	specular = mult3(specular, img.light.brightness);

	c = plus_vec(c, mult3(obj.colour, img.ambient.brightness));
	if (img.light.brightness == 0)
		return (c);
	c = plus_vec(c, mult3(obj.colour, img.light.brightness * dot(r.direction, obj.normal_to_surface)));
	c = plus_vec(c, mult3(specular, powf(img.light.brightness * dot(obj.normal_to_surface, normalize(plus_vec(r.direction, min_vec(img.camera.view_point, obj.intersection)))), 4 * len3(min_vec(img.light.coordinates, obj.intersection)))));
	return (c);
}
