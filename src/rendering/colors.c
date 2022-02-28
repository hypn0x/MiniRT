/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:54:07 by                   #+#    #+#             */
/*   Updated: 2022/02/28 15:57:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <colors.h>
#include <libft.h>
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>
#include <hit_objs.h>

void	format_lights(t_data *img)
{
	t_list	*elem;
	t_light	*light;

	img->ambient.colour = mult3(img->ambient.colour,
			img->ambient.brightness / 255.0f);
	elem = img->light;
	while (elem)
	{
		light = elem->content;
		light->colour = mult3(light->colour, light->brightness / 255.0f);
		elem = elem->next;
	}
}

t_list	*get_hit_elem(t_ray r, t_list **head, float *distance)
{
	float	t;
	t_list	*elem;
	t_list	*hit_elem;

	hit_elem = NULL;
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

t_colour
	get_elem_colour(t_list *hit_elem, t_ray r, t_data img, float distance)
{
	t_object	obj;
	t_point		coordinates;
	t_triangle	t;

	if (hit_elem != NULL)
	{
		obj.intersection = plus_vec(r.origin, mult3(r.direction, distance));
		if (hit_elem->type == 's')
		{
			obj.colour = ((t_sphere *) hit_elem->content)->colour;
			coordinates = ((t_sphere *) hit_elem->content)->coordinates;
		}
		else if (hit_elem->type == 'p')
		{
			obj.colour = ((t_plane *) hit_elem->content)->colour;
			obj.normal_to_surface = ((t_plane *)
					hit_elem->content)->orientation;
		}
		else if (hit_elem->type == 'c')
		{
			obj.colour = ((t_cylinder *) hit_elem->content)->colour;
			coordinates = ((t_cylinder *) hit_elem->content)->coordinates;
		}
		else if (hit_elem->type == 't')
		{
			t = *((t_triangle *) hit_elem->content);
			obj.colour = t.colour;
			obj.normal_to_surface = normalize(cross_prod(min_vec(t.b, t.a), min_vec(t.c, t.a)));
		}
		if (hit_elem->type != 'p' && hit_elem->type != 't')
			obj.normal_to_surface = normalize(min_vec(obj.intersection, coordinates));
		r.origin = plus_vec(obj.intersection,mult3(obj.normal_to_surface,(float)1e-3));
		return (cast_ray(r, img, obj));
	}
	return (new_vec(0.0f, 0.0f, 0.0f));
}
