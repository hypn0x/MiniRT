/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/02/08 13:57:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "parsing/parser.h"
#include <mlx.h>
#include <libft.h>
#include <validate.h>
#include <types.h>
#include <stdlib.h>
#include "../includes/rendering/mlx_img.h"

int	main(int argc, char **argv)
{
	t_list		**objects;
	t_data		img;
	int			fd;

	if (argc != 2)
		return (ft_printf(2, "Usage: ./miniRT (scene)\n"));
	objects = parser(argv[1], &(img.camera), &(img.light), &(img.ambient));
	if (objects == NULL)
		return (ft_printf(2, "Error\nFile scene corrupted\n"));
	else if (check_list_values(*objects, &(img.ambient), &(img.light), &(img.camera)))
	{
		ft_lstclear(objects, free);
		free(objects);
		return (ft_printf(2, "Error\nInvalid value in scene\n"));
	}
	init_image(&img);
	fd = open("/dev/urandom", O_NONBLOCK);
	create_img(objects, &img, fd);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
	close(fd);
}
