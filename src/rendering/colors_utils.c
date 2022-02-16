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
	if (c.x == NAN)
	{
		ft_printf(2, "zero");

	}
	return (rgb);
}

t_colour	get_ray_luminosity(t_data img, t_object obj, t_ray r)
{
	t_colour c = {0, 0, 0};
	t_colour ambient_colour;
	t_colour light_colour;

	ambient_colour = mult3(img.ambient.colour, img.ambient.brightness / 255.0f);
	light_colour = mult3(img.light.colour, img.light.brightness);

	c = plus_vec(c, mult_vec(obj.colour, ambient_colour));
	if (img.light.brightness == 0)
		return (c);
	c = plus_vec(c, mult_vec(obj.colour,mult3(light_colour, dot(r.direction, obj.normal_to_surface) / 255.0f)));
	c = plus_vec(c, mult3(light_colour, powf(img.light.brightness * dot(obj.normal_to_surface, normalize(plus_vec(r.direction, min_vec(img.camera.view_point, obj.intersection)))), 4 * len3(min_vec(img.light.coordinates, obj.intersection)))));
	if (c.x == NAN || c.y == NAN || c.z == NAN)
		ft_printf(2, "err");
	return (c);
}
