/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:37 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/07 20:39:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>

t_vec3	mult3(t_vec3 a, float n)
{
	a.x *= n;
	a.y *= n;
	a.z *= n;
	return (a);
}

t_vec3	div3(t_vec3 a, float n)
{
	a.x /= n;
	a.y /= n;
	a.z /= n;
	return (a);
}

t_vec3	plus3(t_vec3 a, float n)
{
	a.x += n;
	a.y += n;
	a.z += n;
	return (a);
}

t_vec3	min3(t_vec3 a, float n)
{
	a.x -= n;
	a.y -= n;
	a.z -= n;
	return (a);
}

void	swap_vars(float *a, float *b)
{
	float buffer;

	buffer = *a;
	*a = *b;
	*b = buffer;
}

t_vec3 	new_vec(float a, float b, float c)
{
	t_vec3 vec;

	vec.x = a;
	vec.y= b;
	vec.z = c;
	return (vec);
}
