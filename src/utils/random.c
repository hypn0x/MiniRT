//
// Created by segransm on 2/3/22.
//

#include <limits.h>
#include <unistd.h>
#include <constants.h>
#include <stdio.h>

float	rnd(int fd)
{
	static int				i;
	static unsigned char	rand[IMG_W * IMG_W];
	unsigned char			ret;

	if (fd == -1)
		return (.5f);
	if (i == -1)
	{
		if (read(fd, &rand, sizeof(rand)) == -1)
			return (.5f);
		i = sizeof(rand) - 1;
	}
	ret = rand[i];
	i--;
	return ((float)ret / (float)UCHAR_MAX);
}
