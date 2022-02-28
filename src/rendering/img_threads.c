/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:48:30 by                   #+#    #+#             */
/*   Updated: 2022/02/28 15:52:39 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>
#include <constants.h>
#include <float.h>
#include <colors.h>
#include <random.h>
#include <pthread.h>
#include <mlx_img.h>

#include <stdio.h>

t_colour	supersample_px(t_ray ray, t_data img)
{
	int			i;
	t_colour	c;
	t_list		*hit_elem;
	float		distance;

	i = -1;
	c = new_vec(0.0f, 0.0f, 0.0f);
	while (++i < 4)
	{
		ray.direction = normalize(plus_vec(plus_vec(ray.direction,
						mult3(img.vertical, ft_rand(0))),
					mult3(img.horizontal, ft_rand(0))));
		distance = DBL_MAX;
		hit_elem = get_hit_elem(ray, img.objects, &distance);
		c = plus_vec(c, get_elem_colour(hit_elem, ray, img, distance));
	}
	return (div3(c, 4));
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

void	px_loop(t_data img, t_ray ray, t_thread dt)
{
	int		x;
	int		y;
	size_t	px;
	t_vec3	horiz;

	y = dt.start_y - 1;
	px = dt.start_y * IMG_W;
	horiz = mult3(img.horizontal, IMG_W);
	img.light = ft_lstmap(img.light, new_light, free);
	while (++y < (dt.i + 1) * (IMG_H / 12))
	{
		x = -1;
		while (++x < IMG_W)
		{
			ray.direction = plus_vec(ray.direction, img.horizontal);
			dt.img->addr[px++] = get_pixel_value(ray, img);
		}
		ray.direction = plus_vec(ray.direction, img.vertical);
		ray.direction = min_vec(ray.direction, horiz);
	}
	ft_lstclear(&(img.light), free);
}

void	*thread_loop(void *ptr)
{
	t_thread	*dt;
	t_ray		ray;
	t_data		*img;

	dt = ptr;
	img = dt->img;
	ray.origin = img->camera.view_point;
	ray.direction = plus_vec(img->top_left_corner,
			mult3(img->vertical, (float)(dt->start_y - 1)));
	px_loop(*img, ray, *dt);
	return (NULL);
}

void	multithreading(t_data *img)
{
	int			i;
	t_thread	*dt;
	pthread_t	*t;

	dt = malloc(sizeof(t_thread) * 12);
	t = malloc(sizeof(pthread_t) * 12);
	i = -1;
	while (++i < 12)
	{
		dt[i].start_y = i * (IMG_H / 12);
		dt[i].img = img;
		dt[i].i = i;
		pthread_create(&(t[i]), NULL, thread_loop, &(dt[i]));
	}
	i = -1;
	while (++i < 12)
		pthread_join(t[i], NULL);
	free(dt);
	free(t);
}
