/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:24:07 by hsabir            #+#    #+#             */
/*   Updated: 2021/10/14 13:27:13 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t                  i;
	unsigned char   *str;

	i = -1;
	str = (unsigned char *)s;
	while (++i < n)
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
	return (NULL);
}
