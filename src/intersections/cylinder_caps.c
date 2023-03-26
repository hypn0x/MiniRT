/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:33:05 by                   #+#    #+#             */
/*   Updated: 2022/02/28 17:57:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

//t_vec3	vec_unit(t_vec3 vec)
//{
//	float	len;
//
//	len = sqrtf(len3(vec));
//	return (div3(vec, len));
//}
//
//static float	hit_cylinder_cap(t_cylinder *cy, t_ray ray, float t)
//{
//	t_vec3		rt;
//	float		h;
//	float		tp;
//	float		len;
//	int			i;
//
//	i = -1;
//	while (++i < 2)
//	{
//		tp = hit_plane(cy->cap[i], ray);
//		if (tp != -1 && dot(cy->cap[i]->orientation, ray.direction) <= 0)
//		{
//			len = len3(min_vec(cy->cap[i]->coordinates,
//						plus_vec(ray.origin, mult3(ray.direction, tp))));
//			if (len <= powf(cy->diameter / 2, 2))
//				return (tp);
//		}
//	}
//	rt = plus_vec(ray.origin, mult3(ray.direction, t));
//	h = dot(min_vec(rt, cy->coordinates), cy->orientation);
//	if (0 < h && h < cy->height)
//		return (t);
//	return (-1);
//}
//
//void	check_t(float *t, t_cylinder *cylinder, t_ray ray)
//{
//	t_vec3	q;
//	t_vec3	p2;
//
//	p2 = plus_vec(cylinder->coordinates,
//			mult3(cylinder->orientation, cylinder->height));
//	q = plus_vec(ray.origin, mult3(ray.direction, *t));
//	if (dot(cylinder->orientation, min_vec(q, cylinder->coordinates)) <= 0)
//		*t = -1;
//	if (dot(cylinder->orientation, min_vec(q, p2)) >= 0)
//		*t = -1;
//	*t = (hit_cylinder_cap(cylinder, ray, *t));
//}
//
//t_plane	*create_cap(t_vec3 point, t_vec3 normal, t_colour color)
//{
//	t_plane	*pl;
//
//	pl = malloc(sizeof(t_plane));
//	if (!pl)
//		return (NULL);
//	pl->coordinates = point;
//	pl->orientation = vec_unit(normal);
//	pl->colour = color;
//	return (pl);
//}
//
//void	create_caps(t_cylinder *cylinder)
//{
//	cylinder->cap[0] = create_cap(plus_vec(cylinder->coordinates,
//				mult3(cylinder->orientation, cylinder->height)),
//			cylinder->orientation, cylinder->colour);
//	cylinder->cap[1] = create_cap(cylinder->coordinates,
//			mult3(cylinder->orientation, -1), cylinder->colour);
//}
