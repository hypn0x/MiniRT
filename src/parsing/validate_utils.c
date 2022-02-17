/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:59 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/15 17:09:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>
#include <op_vec.h>
#include <math.h>

static int	check_range_vec(t_vec3 v, float lb, float hb)
{
	if (v.x < lb || v.x > hb)
		return (1);
	if (v.y < lb || v.y > hb)
		return (1);
	if (v.z < lb || v.z > hb)
		return (1);
	return (0);
}

int	check_range(float n, float lb, float hb)
{
	return (n < lb || n > hb);
}

int	check_colour(t_colour c)
{
	return (check_range_vec(c, 0.0f, 255.0f));
}

int	check_orientation(t_vec3 o)
{
	return (check_range_vec(o, -1.0f, 1.0f)
		|| isgreaterequal(len3(o) - 1, 1e-6));
}

int	check_brightness(float b)
{
	return (check_range(b, 0.0f, 1.0f));
}
