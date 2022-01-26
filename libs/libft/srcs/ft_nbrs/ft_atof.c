/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:57:43 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/26 10:15:36 by penguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../incs/libft.h"

static void		get_int(int tmp, t_atof *a)
{
	if (a->fraction == 1)
	{
		a->fract_part = a->fract_part * 10 + (tmp - '0');
		a->div *= 10;
	}
	else
		a->int_part = a->int_part * 10 + (tmp - '0');
}

static void		get_sign(char **tmp, t_atof *atof)
{
	if (**tmp == '-')
	{
		if (atof->sign == -1)
			atof->sign = 1;
		else
			atof->sign = -1;
		(*tmp)++;
	}
	else if (**tmp == '+')
		(*tmp)++;
}

static void		init_tmpuct(t_atof *atof)
{
	atof->fraction = 0;
	atof->fract_part = 0;
	atof->int_part = 0;
	atof->div = 1;
	atof->sign = 1;
}

double			ft_atof(const char *str)
{
	t_atof	a;
	int		i;
	char	*tmp;

	i = 0;
	if (!str || !*str)
		return (0);
	tmp = (char *)str;
	init_tmpuct(&a);
	get_sign(&tmp, &a);
	while (tmp[i] != '\0')
	{
		if (tmp[i] >= '0' && tmp[i] <= '9')
			get_int(tmp[i], &a);
		else if (tmp[i] == '.')
		{
			if (a.fraction)
				return (a.sign * (a.int_part + a.fract_part
				/ a.div));
			else
				a.fraction = 1;
		}
		else
			return (a.sign * (a.int_part + a.fract_part / a.div));
		i++;
	}
	return (a.sign * (a.int_part + a.fract_part / a.div));
}
