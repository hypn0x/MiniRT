/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:59:39 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/22 16:59:41 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/libgnl.h"
#include "get_next_line_utils.h"

static int	strchri(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

static char	*read_file(int fd, char *buffer)
{
	char	*dst;
	int		i;

	dst = (char *)gnl_calloc(1, 1);
	dst = gnl_strjoin(dst, buffer);
	while (strchri(dst, '\n') == -1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 1)
		{
			gnl_bzero(buffer, BUFFER_SIZE + 1);
			return (dst);
		}
		buffer[i] = 0;
		dst = gnl_strjoin(dst, buffer);
	}
	return (dst);
}

static void	get_rest(char *dst, char *buffer)
{
	int	i;

	i = strchri(dst, '\n');
	if (i != -1)
		gnl_strlcpy(buffer, &dst[i + 1], BUFFER_SIZE + 1);
	return ;
}

static char	*get_line(char *src)
{
	char	*dst;
	int		size;

	size = strchri(src, '\n') + 1;
	if (size == 0)
	{
		size = gnl_strlen(src);
		if (size == 0)
		{
			free(src);
			return (NULL);
		}
	}
	dst = (char *)gnl_calloc(size + 1, sizeof(char));
	if (!dst)
		return (NULL);
	src[size] = 0;
	gnl_strlcpy(dst, src, size + 1);
	free(src);
	if (dst[0])
		return (dst);
	free(dst);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*dst;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	dst = read_file(fd, buffer);
	get_rest(dst, buffer);
	dst = get_line(dst);
	return (dst);
}
