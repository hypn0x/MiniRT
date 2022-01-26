/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:41:18 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/26 10:14:10 by penguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NBRS_H
# define FT_NBRS_H

typedef struct	s_atof
{
	double	int_part;
	double	fract_part;
	int	div;
	int	sign;
	int	fraction;
}	t_atof;

char	*ft_itoa(int n);
int	ft_atoi(const char *str);
double	ft_atof(const char *str);

#endif
