/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:54:07 by                   #+#    #+#             */
/*   Updated: 2022/02/26 12:58:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Hajar Sabir on 2/8/22.
//

#include "../../includes/rendering/colors.h"
#include <libft.h>
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>
#include <float.h>
#include <hit_objs.h>

t_list	*ray_color(t_ray r, t_list **head, float *distance)
{
	float	t;
	t_list	*elem;
	t_list	*hit_elem;

	hit_elem = NULL;
	*distance = DBL_MAX;
	elem = *head;
	while (elem != NULL)
	{
		t = -1;
		if (elem->type == 's')
			t = hit_sphere(((t_sphere *) elem->content), r);
		else if (elem->type == 'p')
			t = hit_plane(((t_plane *) elem->content), r);
		else if (elem->type == 'c')
			t = hit_cylinder(((t_cylinder *) elem->content), r);
		else if (elem->type == 't')
			t = hit_triangle(((t_triangle *) elem->content), r);
		if (t >= 0 && t <= *distance)
		{
			*distance = t;
			hit_elem = elem;
		}
		elem = elem->next;
	}
	return (hit_elem);
}

t_colour	create_obj(t_list *hit_elem, t_ray r, t_data img, float distance, t_list **head)
{
	t_object	obj;

	if (hit_elem != NULL)
	{
		obj.intersection = plus_vec(r.origin, mult3(r.direction, distance));
		if (hit_elem->type == 's')
		{
			obj.coordinates = ((t_sphere *) hit_elem->content)->coordinates;
			obj.colour = ((t_sphere *) hit_elem->content)->colour;
		}
		else if (hit_elem->type == 'p')
		{
			obj.coordinates = ((t_plane *) hit_elem->content)->coordinates;
			obj.colour = ((t_plane *) hit_elem->content)->colour;
		}
		else if (hit_elem->type == 'c')
		{
			obj.coordinates = ((t_cylinder *) hit_elem->content)->coordinates;
			obj.colour = ((t_cylinder *) hit_elem->content)->colour;
		}
		else if (hit_elem->type == 't')
			obj.colour = ((t_triangle *) hit_elem->content)->colour;
		if (hit_elem->type == 'p')
			obj.normal_to_surface = ((t_plane *) hit_elem->content)->orientation;
		else
			obj.normal_to_surface = normalize(min_vec(obj.intersection, obj.coordinates));
		r.origin = plus_vec(obj.intersection,mult3(obj.normal_to_surface,(float)1e-3));
		return (cast_ray(head, r, img, obj));
	}
	return (new_vec(.0f, 0.0f, 0.0f));
}
