//
// Created by Hajar Sabir on 2/8/22.
//

#ifndef MINIRT_COLORS_H
#define MINIRT_COLORS_H

#include <types.h>

t_list *ray_color(t_ray r, t_list **head, float *distance);

int	rgb_to_int(t_colour c);

t_colour	get_ray_luminosity(t_data img, t_object obj, t_ray r);

t_colour create_obj(t_list *hit_elem, t_ray r, t_data img, float distance, t_list **head);

#endif //MINIRT_COLORS_H
