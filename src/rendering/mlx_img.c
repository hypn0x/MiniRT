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

int	get_pixel_value(t_ray  ray, t_data img, int fd, t_list **objects)
{
	t_colour	val = {0, 0, 0};
	double	distance;
	int px = -1;
	while (++px < SUPERSAMPLING)
	{
		ray.direction = normalize(plus_vec(plus_vec(ray.direction,mult3(img.horizontal,  rnd(fd) / IMG_W)),mult3(img.vertical, rnd(fd) / IMG_H)));
//		ray.direction = normalize(ray.direction);
		t_list *hit_elem = ray_color(ray, objects, &distance);
		val = plus_vec(val, create_obj(hit_elem, ray, img, distance, objects));
	}
	return (rgb_to_int(div3(val, SUPERSAMPLING)));
}

void create_img(t_list **objects, t_data *img, int fd)
{
	int y;
	int x;
	t_ray ray;

	y = -1;
	ray.origin = img->camera.view_point;
	ray.direction = img->top_left_corner;
	while (++y < IMG_H)
	{
		x = -1;
		while (++x < IMG_W)
		{
			ray.direction = plus_vec(ray.direction,  mult3(img->horizontal,1.0 / IMG_W));
			img->addr[y * IMG_W + x] = get_pixel_value(ray, *img, fd, objects);
		}
		ray.direction = plus_vec(ray.direction,  mult3(img->vertical,1.0 / IMG_H));
		ray.direction = min_vec(ray.direction,  img->horizontal);
	}
}
