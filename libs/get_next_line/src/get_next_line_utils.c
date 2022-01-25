/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:01:37 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/22 17:01:38 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

size_t	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	gnl_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dst;

	i = -1;
	dst = (unsigned char *)s;
	while (++i < n)
		dst[i] = 0;
}

void	*gnl_calloc(size_t count, size_t size)
{
	size_t	s;
	void	*m;

	s = count * size;
	m = malloc(s);
	if (m == NULL)
		return (NULL);
	gnl_bzero(m, s);
	return (m);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1l = gnl_strlen(s1);
	s2l = gnl_strlen(s2);
	str = (char *)gnl_calloc(s1l + gnl_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	gnl_strlcpy(str, s1, s1l + 1);
	gnl_strlcpy(str + s1l, s2, s2l + 1);
	free(s1);
	return (str);
}
