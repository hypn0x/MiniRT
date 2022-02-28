/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/02/28 16:59:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <mlx.h>
#include <libft.h>
#include <validate.h>
#include <types.h>
#include <stdlib.h>
#include <mlx_img.h>
#include <constants.h>
#include <random.h>
#include <time.h>

static void	create_img(t_data *img)
{
	time_t	t;

	if (SUPERSAMPLING)
	{
		ft_rand(time(&t));
		multithreading(img);
	}
	else
		img_loop(img);
}

int	main(int argc, char **argv)
{
	t_data		img;

	if (argc != 2)
		return (ft_printf(2, "Usage: ./miniRT (scene)\n"));
	parser(argv[1], &img);
	if (img.objects == NULL)
		return (ft_printf(2, "Error\nFile scene corrupted\n"));
	else if (check_list_values(*(img.objects),
			&(img.ambient), img.light, &(img.camera)))
	{
		ft_lstclear(img.objects, free);
		ft_lstclear(&(img.light), free);
		free(img.objects);
		return (ft_printf(2, "Error\nInvalid value in scene\n"));
	}
	init_image(&img);
	create_img(&img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
}
