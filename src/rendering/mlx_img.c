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
#include "../includes/rendering/colors.h"


void	init_image(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, IMG_W, IMG_H, "MiniRT!");
	img->img = mlx_new_image(img->mlx, IMG_W, IMG_H);
	img->addr = (int *) mlx_get_data_addr(img->img, &(img->bbp), &(img->line_len), &(img->endian));
	// convert fov from degrees to radiant
	img->camera.fov = img->camera.fov * (float)M_PI / 180.0f;
	img->viewport_width = tanf(img->camera.fov / 2) * 2;
	img->viewport_height = img->viewport_width / ASPECT_RATIO;
	t_vec3 y = {0, 1, 0};
	img->horizontal = cross_prod(img->camera.orientation, y);
	img->vertical = mult3(cross_prod(img->camera.orientation, img->horizontal), img->viewport_height);
	img->horizontal = mult3(img->horizontal, img->viewport_width);
	img->top_left_corner = min_vec(plus_vec(min_vec(min_vec(img->camera.view_point, div3(img->horizontal, 2)), div3(img->vertical, 2)), img->camera.orientation), img->camera.view_point);
	img->vertical = div3(img->vertical, IMG_H); // todo: fix case where cross prod = 0
	img->horizontal = div3(img->horizontal, IMG_W);
	mlx_hook(img->mlx_win, 17, 1L, ft_exit, img);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
}

int	get_pixel_value(t_ray  ray, t_data img, t_list **objects)
{
	t_colour	val = {0, 0, 0};
	float	distance;

	ray.direction = normalize(ray.direction);
	t_list *hit_elem = ray_color(ray, objects, &distance);
	val = plus_vec(val, create_obj(hit_elem, ray, img, distance, objects));
	return (rgb_to_int(div3(val, 1)));
}

void create_img(t_list **objects, t_data *img)
{
	int y;
	int x;
	int px;
	t_ray ray;
	t_vec3 horiz = mult3(img->horizontal, IMG_W);

	y = -1;
	px = 0;
	ray.origin = img->camera.view_point;
	ray.direction = img->top_left_corner;
	while (++y < IMG_H)
	{
		x = -1;
		while (++x < IMG_W)
		{
			ray.direction = plus_vec(ray.direction,  img->horizontal);
			img->addr[px++] = get_pixel_value(ray, *img, objects);
		}
		ray.direction = plus_vec(ray.direction,  img->vertical);
		ray.direction = min_vec(ray.direction,  horiz);
	}
}
