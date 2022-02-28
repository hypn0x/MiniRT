/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:51:42 by                   #+#    #+#             */
/*   Updated: 2022/02/28 17:51:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <colors.h>
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

t_colour	get_diffuse_light(t_object obj, t_light light, t_ray r)
{
	return (mult_vec(obj.colour, mult3(light.colour,
				dot(r.direction, obj.normal_to_surface))));
}

t_colour	get_specular_light(t_object obj, t_light light, t_ray r, t_data img)
{
	float	brightness;

	brightness = light.brightness * fabsf(dot(obj.normal_to_surface,
				normalize(plus_vec(r.direction,
						min_vec(img.camera.view_point, obj.intersection)))));
	return (mult3(light.colour, powf(brightness, 100
				* len3(min_vec(light.coordinates, obj.intersection)))
			* 255.0f));
}

t_colour	get_pixel_colour(t_data img, t_object obj, t_ray r)
{
	t_colour	c;
	t_list		*elem;
	t_light		*light;

	c = mult_vec(obj.colour, img.ambient.colour);
	elem = img.light;
	while (elem)
	{
		light = elem->content;
		if (light->brightness < 0)
		{
			light->brightness = -light->brightness;
			elem = elem->next;
			continue ;
		}
		r.direction = normalize(min_vec(light->coordinates, r.origin));
		if (dot(r.direction, obj.normal_to_surface) < 0)
			obj.normal_to_surface = mult3(obj.normal_to_surface, -1);
		c = plus_vec(c, get_diffuse_light(obj, *light, r));
		c = plus_vec(c, get_specular_light(obj, *light, r, img));
		elem = elem->next;
	}
	return (c);
}
