/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:57:43 by hsabir            #+#    #+#             */
/*   Updated: 2022/02/21 12:02:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../incs/libft.h"

static void	get_int(int tmp, t_atof *a)
{
	if (a->fraction == 1)
	{
		a->fract_part = a->fract_part * 10 + (tmp - '0');
		a->div *= 10;
	}
	else
		a->int_part = a->int_part * 10 + (tmp - '0');
}

static void	get_sign(char **tmp, t_atof *atof)
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

static void	init_struct(t_atof *atof)
{
	atof->fraction = 0;
	atof->fract_part = 0;
	atof->int_part = 0;
	atof->div = 1;
	atof->sign = 1;
}

float	do_while(t_atof *a, char *tmp)
{
	int		i;
	int		cntr;

	i = 0;
	cntr = 0;
	while (tmp[i] != '\0')
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '.')
			return (1);
		if (tmp[i] >= '0' && tmp[i] <= '9')
			get_int(tmp[i], a);
		else if (tmp[i] == '.' && cntr <= 1)
		{
			cntr++;
			if (a->fraction)
				return (a->sign * (a->int_part + a->fract_part / a->div));
			else
				a->fraction = 1;
		}
		else
			return (a->sign * (a->int_part + a->fract_part / a->div));
		i++;
	}
	return (0);
}

int	ft_atof(const char *str, float *n)
{
	t_atof	a;
	char	*tmp;
	float	fn;

	if (!str || !*str)
		return (1);
	tmp = (char *)str;
	init_struct(&a);
	get_sign(&tmp, &a);
	fn = do_while(&a, tmp);
	if (!fn)
		*n = (a.sign * (a.int_part + a.fract_part / a.div));
	return (0);
}
