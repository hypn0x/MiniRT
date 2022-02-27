/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:37:05 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/18 14:02:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_VEC_H
# define OP_VEC_H

# include <types.h>

t_vec3	min_vec(t_vec3 a, t_vec3 b);

t_vec3	plus_vec(t_vec3 a, t_vec3 b);

t_vec3	mult_vec(t_vec3 a, t_vec3 b);

float	dot(t_vec3 a, t_vec3 b);

float	len3(t_vec3 a);

t_vec3	normalize(t_vec3 a);

t_vec3	cross_prod(t_vec3 a, t_vec3 b);

t_vec3	vec_unit(t_vec3 vec);

#endif //OP_VEC_H
