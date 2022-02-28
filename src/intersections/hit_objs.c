/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:44:48 by                   #+#    #+#             */
/*   Updated: 2022/02/28 18:31:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <types.h>
#include <hit_objs.h>
#include <colors.h>
#include <op_vec.h>

float	get_t(t_list *elem, float t, t_ray r)
{
	if (elem->type == 's')
		t = hit_sphere(((t_sphere *) elem->content), r);
	else if (elem->type == 'p')
		t = hit_plane(((t_plane *) elem->content), r);
	else if (elem->type == 'c')
		t = hit_cylinder(((t_cylinder *) elem->content), r);
	else if (elem->type == 't')
		t = hit_triangle(((t_triangle *)elem->content), r);
	return (t);
}

// td[0] = t
// td[1] = distance to light

t_colour	cast_ray(t_ray r, t_data img, t_object obj)
{
	t_list	*elem;
	t_list	*cl;
	t_light	*light;
	float	td[2];

	cl = img.light;
	while (cl)
	{
		light = cl->content;
		elem = *(img.objects);
		td[1] = len3(min_vec(light->coordinates, r.origin));
		r.direction = normalize(min_vec(light->coordinates, r.origin));
		while (elem != NULL)
		{
			td[0] = get_t(elem, td[0], r);
			if (td[0] > 0 && td[0] < td[1] - (float)1e-5)
			{
				light->brightness = -light->brightness;
				break ;
			}
			elem = elem->next;
		}
		cl = cl->next;
	}
	return (get_pixel_colour(img, obj, r));
}
