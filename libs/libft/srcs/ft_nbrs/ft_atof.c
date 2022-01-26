/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:57:43 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/25 17:51:52 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../incs/libft.h"

double	a_pow(double base, double power)
{
	double	mem;

	mem = base;
	while (power < -1)
	{
		base = base * mem;
		power++;
	}
	return (1 / base);
}

double	ft_atof(const char *str)
{
	int		i;
	int		j;
	char	*c;
	double	value;
	int		a_point;

	i = 0;
	j = 0;
	a_point = 0;
	c = (char *)str;
	while (c[i] != '\0')
	{
		if (str[i] != '.')
		{
			value = (value * 10) + (c[i] - '0');
			if (a_point == 1)
				--j;
		}
		if (c[i] == '.')
		{	
			if (a_point == 1)
				return (0);
			a_point = 1;
		}
		i++;
	}
	value = value * a_pow(10, j); 
	return (value);
}
