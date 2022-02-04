//
// Created by segransm on 2/3/22.
//

#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <constants.h>
#include <stdio.h>
double rnd(int fd)
{
	static int				i;
	static unsigned char	rand[IMG_W * IMG_W];
	unsigned char			ret;
	static int j;
	if (fd == -1)
		return (.5);
	if (i == -1)
	{
		printf("%d\n", j++);
		if (read(fd, &rand, sizeof(rand)) == -1)
			return (.5);
		i = sizeof(rand) - 1;
	}
	ret = rand[i];
	i--;
	return ((double)ret / (double)UCHAR_MAX);
}
