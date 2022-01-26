//
// Created by segransm on 1/26/22.
//

#ifndef OP_VEC_H
# define OP_VEC_H

#include <types.h>

t_vec3	min_vec(t_vec3 a, t_vec3 b);

t_vec3	plus_vec(t_vec3 a, t_vec3 b);

double	dot(t_vec3 a, t_vec3 b);

t_vec3	unit_vector(t_vec3 a);

#endif //OP_VEC_H
