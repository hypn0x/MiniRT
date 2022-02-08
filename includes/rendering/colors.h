//
// Created by Hajar Sabir on 2/8/22.
//

#ifndef MINIRT_COLORS_H
#define MINIRT_COLORS_H

#include <types.h>

t_colour ray_color(t_ray r, t_list **head, t_data img);

int	rgb_to_int(t_colour c);

t_colour	get_ray_luminosity(t_data img, t_object obj, t_ray r);

#endif //MINIRT_COLORS_H
