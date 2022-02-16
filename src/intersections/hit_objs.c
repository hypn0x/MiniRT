//
// Created by Hajar Sabir on 2/7/22.
//

#include <libft.h>
#include <types.h>
#include <hit_objs.h>
#include "../includes/rendering/colors.h"

t_colour	cast_ray(t_list **head, t_ray r, t_data img, t_object obj, t_list *hit_elem)
{
	t_list	*elem;
	float	t;

	elem = *head;
	t = -1;
	while (elem != NULL)
	{
		if (elem == hit_elem)
		{
			elem = elem->next;
			continue ;
		}
		if (elem->type == 's')
			t = hit_sphere(((t_sphere *) elem->content), r);
		else if (elem->type == 'p')
			t = hit_plane(((t_plane *) elem->content), r);
		else if (elem->type == 'c')
			t = hit_cylinder(((t_cylinder *) elem->content), r);
		if (t > 0)
		{
			img.light.brightness = 0;
			return (get_ray_luminosity(img, obj, r));
		}
		elem = elem->next;
	}
	return (get_ray_luminosity(img, obj, r));
}
