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



t_list *ray_color(t_ray r, t_list **head, float *distance)
{
	float t;
	t_list *elem;
	t_list *hit_elem;

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
		if (t >= 0 && t <= *distance)
		{
			*distance = t;
			hit_elem = elem;
		}
		elem = elem->next;
	}
	return (hit_elem);
}

t_vec3 		get_cylinder_normal(t_vec3 point, t_cylinder cylinder)
{
	t_vec3 ctp;
	t_vec3 normal;

	ctp = min_vec(point, cylinder.coordinates);
	normal = min_vec(ctp, mult3(cylinder.orientation,
								dot(cylinder.orientation, ctp)));
	normal = normalize(normal);
	return (normal);
}

t_colour create_obj(t_list *hit_elem, t_ray r, t_data img, float distance, t_list **head)
{
	t_object obj;

	if (hit_elem != NULL)
	{
		obj.intersection = plus_vec(r.origin, mult3(r.direction, distance));
		if (hit_elem->type == 's')
		{
			obj.coordinates = ((t_sphere *) hit_elem->content)->coordinates;
			obj.colour = ((t_sphere *) hit_elem->content)->colour;
			obj.normal_to_surface = normalize(min_vec(obj.intersection, obj.coordinates));
			r.origin = obj.intersection;
			r.direction = normalize(min_vec(img.light.coordinates, r.origin));
		}
		else if (hit_elem->type == 'p')
		{
			obj.coordinates = ((t_plane *) hit_elem->content)->coordinates;
			obj.colour = ((t_plane *) hit_elem->content)->colour;
			obj.normal_to_surface = ((t_plane *) hit_elem->content)->orientation;
			r.direction = normalize(min_vec(img.light.coordinates, obj.intersection));
			if (dot(r.direction, obj.normal_to_surface) < 0)
				obj.normal_to_surface = mult3(obj.normal_to_surface, -1);
			r.origin = obj.intersection;
		}
		else if (hit_elem->type == 'c')
		{
			obj.coordinates = ((t_cylinder *) hit_elem->content)->coordinates;
			obj.colour = ((t_cylinder *) hit_elem->content)->colour;
			obj.normal_to_surface = normalize(min_vec(obj.intersection, obj.coordinates));
			obj.distance_to_light = len3(min_vec(img.light.coordinates, r.origin));
			r.origin = obj.intersection;
			r.direction = normalize(min_vec(img.light.coordinates, r.origin));
		}
		return (cast_ray(head, r, img, obj, hit_elem));
	}
	t_colour c = {0, 0, 0};
	return (c);
}
