/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:34:48 by                   #+#    #+#             */
/*   Updated: 2022/02/28 15:44:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <types.h>
#include <op_vec.h>
#include <math.h>
#include <constants.h>
#include <float.h>
#include <colors.h>
#include <pthread.h>
#include <mlx_img.h>

// todo: fix case where cross prod = 0 l:38
void	init_image(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, IMG_W, IMG_H, "MiniRT!");
	img->img = mlx_new_image(img->mlx, IMG_W, IMG_H);
	img->addr = (int *)mlx_get_data_addr(img->img, &(img->bbp),
			&(img->line_len), &(img->endian));
	img->camera.fov = img->camera.fov * (float)M_PI / 180.0f;
	img->viewport_width = tanf(img->camera.fov / 2) * 2;
	img->viewport_height = img->viewport_width / ASPECT_RATIO;
	img->horizontal = cross_prod(img->camera.orientation,
			new_vec(0.0f, 1.0f, 0.0f));
	img->vertical = mult3(cross_prod(img->camera.orientation, img->horizontal),
			img->viewport_height);
	img->horizontal = mult3(img->horizontal, img->viewport_width);
	img->top_left_corner = min_vec(plus_vec(min_vec(min_vec(
						img->camera.view_point, div3(img->horizontal, 2)),
					div3(img->vertical, 2)), img->camera.orientation),
			img->camera.view_point);
	img->vertical = div3(img->vertical, IMG_H);
	img->horizontal = div3(img->horizontal, IMG_W);
	format_lights(img);
	mlx_hook(img->mlx_win, 17, 1L, ft_exit, img);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
}

static t_colour	get_mean_pixel(t_ray ray, t_data img)
{
	t_colour	val;
	t_list		*hit_elem;
	t_vec3		top_left;
	float		distance;

	top_left = ray.direction;
	ray.direction = normalize(top_left);
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = get_elem_colour(hit_elem, ray, img, distance);
	ray.direction = normalize(plus_vec(top_left, img.horizontal));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = plus_vec(val, get_elem_colour(hit_elem, ray, img, distance));
	ray.direction = normalize(plus_vec(top_left, img.vertical));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = plus_vec(val, get_elem_colour(hit_elem, ray, img, distance));
	ray.direction = normalize(plus_vec(plus_vec(top_left, img.vertical),
				img.horizontal));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = plus_vec(val, get_elem_colour(hit_elem, ray, img, distance));
	return (div3(val, 4));
}

int	is_px_diff(t_colour c1, t_colour c2)
{
	float	diff;

	diff = 2.0f;
	if (c1.x - diff > c2.x || c1.x + diff < c2.x)
		return (1);
	if (c1.y - diff > c2.y || c1.y + diff < c2.y)
		return (1);
	if (c1.z - diff > c2.z || c1.z + diff < c2.z)
		return (1);
	return (0);
}

int	get_pixel_value(t_ray ray, t_data img)
{
	t_colour	v1;
	t_colour	v2;
	t_vec3		top_left;
	t_list		*hit_elem;
	float		distance;

	if (SUPERSAMPLING)
		v1 = get_mean_pixel(ray, img);
	top_left = ray.direction;
	ray.direction = normalize(plus_vec(plus_vec(ray.direction,
					mult3(img.vertical, 0.5f)), mult3(img.horizontal, 0.5f)));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	v2 = get_elem_colour(hit_elem, ray, img, distance);
	ray.direction = top_left;
	if (SUPERSAMPLING && is_px_diff(v1, v2))
		return (rgb_to_int(div3(plus_vec(v1,
						plus_vec(v2, supersample_px(ray, img))), 3)));
	if (SUPERSAMPLING)
		return (rgb_to_int(div3(plus_vec(v1, v2), 2)));
	return (rgb_to_int(v2));
}

void	img_loop(t_data *img)
{
	size_t	x;
	size_t	y;
	size_t	px;
	t_vec3	horiz;
	t_ray	ray;

	horiz = mult3(img->horizontal, IMG_W);
	y = -1;
	px = 0;
	ray.origin = img->camera.view_point;
	ray.direction = img->top_left_corner;
	while (++y < IMG_H)
	{
		x = -1;
		while (++x < IMG_W)
		{
			ray.direction = plus_vec(ray.direction, img->horizontal);
			img->addr[px++] = get_pixel_value(ray, *img);
		}
		ray.direction = plus_vec(ray.direction, img->vertical);
		ray.direction = min_vec(ray.direction, horiz);
	}
}
