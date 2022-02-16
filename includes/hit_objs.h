//
// Created by Hajar Sabir on 2/7/22.
//

#ifndef MINIRT_HIT_OBJS_H
#define MINIRT_HIT_OBJS_H

# include <types.h>


t_colour	cast_ray(t_list **head, t_ray r, t_data img, t_object obj, t_list *hit_elem);
float	hit_sphere(const t_sphere *sphere, t_ray r);
float	hit_plane(t_plane *plane, t_ray r);
float	hit_cylinder(t_cylinder *cylinder, t_ray r);


#endif //MINIRT_HIT_OBJS_H
