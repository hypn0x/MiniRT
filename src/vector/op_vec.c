/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:31 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/21 14:26:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>
#include <math.h>

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

float	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	len3(t_vec3 a)
{
	return (sqrtf(dot(a, a)));
}

t_vec3	normalize(t_vec3 a)
{
	return (div3(a, len3(a)));
}
