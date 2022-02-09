/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:31 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/07 20:39:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>
#include <math.h>
#include <op_vec_double.h>

t_vec3	min_vec(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3	plus_vec(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

double	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	len3(t_vec3 a)
{
	return (sqrt(dot(a, a)));
}

t_vec3	normalize(t_vec3 a)
{
	return (div3(a, len3(a)));
}

t_vec3 	cross_prod(t_vec3 a, t_vec3 b)
{
	t_vec3 	new;

	new.x = a.y * b.z - a.z * b.y;
	new.y = a.z * b.x - a.x * b.z;
	new.z = a.x * b.y - a.y * b.x;
	return (new);
}
