/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:44:48 by                   #+#    #+#             */
/*   Updated: 2022/02/21 14:44:53 by                  ###   ########.fr       */
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

t_colour	cast_ray(t_list **head, t_ray r, t_data img, t_object obj)
{
	t_list	*elem;
	float	t;

	elem = *head;
	t = -1;
	while (elem != NULL)
	{
		if (elem->type == 's')
			t = hit_sphere(((t_sphere *) elem->content), r);
		else if (elem->type == 'p')
			t = hit_plane(((t_plane *) elem->content), r);
		else if (elem->type == 'c')
			t = hit_cylinder(((t_cylinder *) elem->content), r);
		if (t > 0 && t < obj.distance_to_light - (float)1e-5)
		{
			img.light.brightness = 0;
			return (get_ray_luminosity(img, obj, r));
		}
		elem = elem->next;
	}
	return (get_ray_luminosity(img, obj, r));
}
