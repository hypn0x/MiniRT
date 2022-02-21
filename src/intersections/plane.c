/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:33:13 by                   #+#    #+#             */
/*   Updated: 2022/02/21 14:43:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

float	hit_plane(t_plane *plane, t_ray r)
{
	float	dn_dot;
	float	t;
	t_vec3	p0l0;

	dn_dot = dot(plane->orientation, r.direction);
	if (islessgreater(dn_dot, (float)1e-6))
	{
		p0l0 = min_vec(plane->coordinates, r.origin);
		t = dot(p0l0, plane->orientation) / dn_dot;
		if (t > 0)
			return (t);
	}
	return (-1);
}
