/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:46:34 by                   #+#    #+#             */
/*   Updated: 2022/02/21 14:46:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

float	ft_rand(unsigned long seed)
{
	static unsigned long	lfsr;

	if (!lfsr)
		lfsr = seed;
	lfsr ^= lfsr << 13;
	lfsr ^= lfsr >> 7;
	lfsr ^= lfsr << 17;
	return ((float)lfsr / (float)ULLONG_MAX);
}
