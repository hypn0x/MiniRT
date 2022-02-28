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
#include <op_vec_double.h>
#include <op_vec.h>
#include <math.h>
#include <constants.h>
#include <float.h>
#include <colors.h>
#include <random.h>
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

t_colour	get_mean_pixel(t_ray ray, t_data img)
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

void	*new_light(void *content)
{
	t_light	*light;
	t_light	*new_light;

	light = content;
	new_light = malloc(sizeof(t_light));
	if (!new_light)
		return (NULL);
	new_light->colour = light->colour;
	new_light->brightness = light->brightness;
	new_light->coordinates = light->coordinates;
	return (new_light);
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

// nor = y[0], x[1], px[2]
// TODO norminette

void	create_img(t_data *img)
{
	int		nor[3];
	t_ray	ray;
	t_vec3	horiz;
	time_t	t;

	if (SUPERSAMPLING)
	{
		ft_rand(time(&t));
		multithreading(img);
	}
	else
	{
		horiz = mult3(img->horizontal, IMG_W);
		nor[0] = -1;
		nor[2] = 0;
		ray.origin = img->camera.view_point;
		ray.direction = img->top_left_corner;
		while (++nor[0] < IMG_H)
		{
			nor[1] = -1;
			while (++nor[1] < IMG_W)
			{
				ray.direction = plus_vec(ray.direction, img->horizontal);
				img->addr[nor[2]++] = get_pixel_value(ray, *img);
			}
			ray.direction = plus_vec(ray.direction, img->vertical);
			ray.direction = min_vec(ray.direction, horiz);
		}
	}
}
