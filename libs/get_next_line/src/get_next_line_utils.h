//
// Created by segransm on 1/25/22.
//

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

#include <stdlib.h>

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);

size_t	gnl_strlen(const char *s);

char	*gnl_strjoin(char *s1, char *s2);

void	*gnl_calloc(size_t count, size_t size);

void	gnl_bzero(void *s, size_t n);

#endif //GET_NEXT_LINE_UTILS_H
