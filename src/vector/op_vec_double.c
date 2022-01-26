/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:37 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/27 00:12:40 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>

t_vec3	mult3(t_vec3 a, double n)
{
	a.x *= n;
	a.y *= n;
	a.z *= n;
	return (a);
}

t_vec3	div3(t_vec3 a, double n)
{
	a.x /= n;
	a.y /= n;
	a.z /= n;
	return (a);
}

t_vec3	plus3(t_vec3 a, double n)
{
	a.x += n;
	a.y += n;
	a.z += n;
	return (a);
}

t_vec3	min3(t_vec3 a, double n)
{
	a.x -= n;
	a.y -= n;
	a.z -= n;
	return (a);
}
