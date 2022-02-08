/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec_double.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:36:58 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/07 15:08:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_VEC_DOUBLE_H
# define OP_VEC_DOUBLE_H

# include <types.h>

t_vec3	mult3(t_vec3 a, double n);

t_vec3	div3(t_vec3 a, double n);

t_vec3	plus3(t_vec3 a, double n);

t_vec3	min3(t_vec3 a, double n);

void		swap_vars(double *a, double *b);
t_vec3 	new_vec(double a, double b, double c);

#endif //OP_VEC_DOUBLE_H
