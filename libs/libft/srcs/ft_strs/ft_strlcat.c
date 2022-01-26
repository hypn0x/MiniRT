/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:52:28 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/26 11:34:08 by 0xb1n4r          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	tmp;
	size_t	len;

	len = 0;
	while (dst[len] && len < size)
		len++;
	tmp = len;
	while (src[len - tmp] && len + 1 < size)
	{
		dst[len] = src[len - tmp];
		len++;
	}
	if (tmp < size)
		dst[len] = '\0';
	return (tmp + ft_strlen(src));
}
