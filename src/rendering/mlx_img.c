//
// Created by Hajar Sabir on 2/8/22.
//

#include <mlx.h>
#include <libft.h>
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>
#include <math.h>
#include <constants.h>
#include <rotate_vec.h>
#include <random.h>
#include "../includes/rendering/colors.h"


void	init_image(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, IMG_W, IMG_H, "MiniRT!");
	img->img = mlx_new_image(img->mlx, IMG_W, IMG_H);
	img->addr = (int *) mlx_get_data_addr(img->img, &(img->bbp), &(img->line_len), &(img->endian));
	// convert fov from degrees to radiant
	img->camera.fov = img->camera.fov * M_PI / 180;
	img->viewport_width = tan(img->camera.fov / 2) * 2;
	img->viewport_height = img->viewport_width / ASPECT_RATIO;
	// pi/2 is 90 degrees
	img->horizontal = mult3(rotate_y_axis(-M_PI_2, img->camera.orientation), img->viewport_width);
	img->vertical = mult3(rotate_x_axis(-M_PI_2, img->camera.orientation), img->viewport_height);
	img->top_left_corner = plus_vec(min_vec(min_vec(img->camera.view_point, div3(img->horizontal, 2)), div3(img->vertical, 2)), img->camera.orientation);
	mlx_hook(img->mlx_win, 17, 1L, ft_exit, img);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
}


void	create_img(t_list **objects, t_data	*img, int fd)
{
	int		y;
	int		x;
	t_ray	ray;
	int		px;

	y = -1;
	ray.origin = img->camera.view_point;
	ray.direction = img->top_left_corner;
	px = 0;
	while (++y < IMG_H)
	{
		x = -1;
		while (++x < IMG_W)
		{
			if (SUPERSAMPLING == 0)
			{
				ray.direction = normalize(min_vec(plus_vec(plus_vec(img->top_left_corner,
																	mult3(img->horizontal, ((double) x + .5) / IMG_W)),
														   mult3(img->vertical, ((double) y + .5) / IMG_H)),
												  ray.origin));
				img->addr[y * IMG_W + x] = rgb_to_int(ray_color(ray, objects, *img));
			}
			else
			{
				t_colour	val = {0, 0, 0};
				px = -1;
				while (++px < SUPERSAMPLING)
				{
					ray.direction = normalize(min_vec(plus_vec(plus_vec(img->top_left_corner,
																		mult3(img->horizontal, ((double) x + rnd(fd)) / IMG_W)),
															   mult3(img->vertical, ((double) y + rnd(fd)) / IMG_H)),
													  ray.origin));
					val = plus_vec(val, ray_color(ray, objects, *img));
				}
				img->addr[y * IMG_W + x] = rgb_to_int(div3(val, SUPERSAMPLING));
			}
		}
	}
}
