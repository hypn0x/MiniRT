//
// Created by Hajar Sabir on 2/8/22.
//

#ifndef COLORS_H
# define COLORS_H

# include <types.h>

t_list		*get_hit_elem(t_ray r, t_list **head, float *distance);

int			rgb_to_int(t_colour c);

t_colour	get_pixel_colour(t_data img, t_object obj, t_ray r);

t_colour	create_obj(t_list *hit_elem, t_ray r, t_data img, float distance);

#endif //COLORS_H
