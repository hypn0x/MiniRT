/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:44:48 by                   #+#    #+#             */
/*   Updated: 2022/02/26 12:57:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Hajar Sabir on 2/7/22.
//

#include <libft.h>
#include <types.h>
#include <hit_objs.h>
#include <math.h>
#include <colors.h>
#include "op_vec.h"

t_colour	cast_ray(t_ray r, t_data img, t_object obj)
{
	t_list	*elem;
	t_list	*L;
	t_light	*light;
	float	t;
	float	distance_to_light;

	L = img.light;
	while (L)
	{
		light = L->content;
		elem = *(img.objects);
		t = -1;
		distance_to_light = len3(min_vec(light->coordinates, r.origin));
		r.direction = normalize(min_vec(light->coordinates, r.origin));
		while (elem != NULL)
		{
			if (elem->type == 's')
				t = hit_sphere(((t_sphere *) elem->content), r);
			else if (elem->type == 'p')
				t = hit_plane(((t_plane *) elem->content), r);
			else if (elem->type == 'c')
				t = hit_cylinder(((t_cylinder *) elem->content), r);
			else if (elem->type == 't')
				t = hit_triangle(((t_triangle *)elem->content), r);
			if (t > 0 && t < distance_to_light - (float)1e-5)
			{
				light->brightness = -light->brightness;
				break ;
			}
			elem = elem->next;
		}
		L = L->next;
	}
	return (get_pixel_colour(img, obj, r));
}
