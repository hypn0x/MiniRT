//
// Created by Hajar Sabir on 2/7/22.
//

#ifndef MINIRT_HIT_OBJS_H
#define MINIRT_HIT_OBJS_H

# include <types.h>

double	hit_sphere(const t_sphere *sphere, t_ray r);
double	hit_plane(t_plane *plane, t_ray r);
double	hit_cylinder(t_cylinder *cylinder, t_ray r);


#endif //MINIRT_HIT_OBJS_H
