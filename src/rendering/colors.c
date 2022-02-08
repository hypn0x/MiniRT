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



t_colour ray_color(t_ray r, t_list **head, t_data img) {
	double		distance;
	double		t;
	t_list		*elem;
	t_list		*hit_elem;
	t_object	obj;

	hit_elem = NULL;
	distance = DBL_MAX;
	elem = *head;
	t = -1;
	while (elem != NULL) {
		if (elem->type == 's')
			t = hit_sphere(((t_sphere *) elem->content), r);
		else if (elem->type == 'p')
			t = hit_plane(((t_plane *) elem->content), r);
		else if (elem->type == 'c')
		{
			t = hit_cylinder(((t_cylinder *) elem->content), r);
//			if (t > 0)
//				return (((t_cylinder *) elem->content)->colour);
		}
		if (t >= 0 && t < distance)
		{
			distance = t;
			t = -1;
			hit_elem = elem;
		}
		elem = elem->next;
	}
	if (hit_elem != NULL) {

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

		obj.intersection = plus_vec(r.origin, mult3(r.direction, distance));
		obj.normal_to_surface = normalize(min_vec(obj.intersection, ((t_sphere *) hit_elem->content)->coordinates));
		r.origin = plus_vec(obj.intersection,mult3(obj.normal_to_surface,1e-5));
		r.direction = normalize(min_vec(img.light.coordinates, r.origin));
		return (cast_ray(head, r, img, obj));
	}
	t_colour c = {0, 0, 0};
	return (c);
}