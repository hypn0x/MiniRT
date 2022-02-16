/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:41:18 by hsabir            #+#    #+#             */
/*   Updated: 2022/02/15 17:09:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NBRS_H
# define FT_NBRS_H

typedef struct	s_atof
{
	float	int_part;
	float	fract_part;
	int	div;
	int	sign;
	int	fraction;
}	t_atof;

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_atof(const char *str, float *n);

#endif
