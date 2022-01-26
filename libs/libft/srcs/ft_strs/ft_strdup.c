/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:07:06 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/26 11:34:08 by 0xb1n4r          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*copy;

	slen = ft_strlen(s1);
	copy = malloc(sizeof(char) * (slen + 1));
	if (!copy)
		return (NULL);
	slen = 0;
	while (s1[slen])
	{
		copy[slen] = s1[slen];
		slen++;
	}
	copy[slen] = '\0';
	return (copy);
}
