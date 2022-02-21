/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:45:22 by                   #+#    #+#             */
/*   Updated: 2022/02/21 14:45:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Hajar Sabir on 2/8/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

float	hit_sphere(const t_sphere *sphere, t_ray r)
{
	float	rd;
	float	b;
	float	lt1;
	float	ct2;

	rd = sphere->diameter / 2;
	b = 2 * dot(r.direction, min_vec(r.origin, sphere->coordinates));
	lt1 = len3(min_vec(r.origin, sphere->coordinates));
	ct2 = (lt1 * lt1) - (rd * rd);
	rd = b * b - 4 * ct2;
	if (rd >= 0)
	{
		lt1 = (-b + sqrtf(rd)) / 2;
		ct2 = (-b - sqrtf(rd)) / 2;
		if (lt1 > 0 && ct2 > 0)
		{
			if (lt1 < ct2)
				return (lt1);
			return (ct2);
		}
	}
	return (-1);
}
