/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/02/07 20:09:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parser.h"
#include <mlx.h>
#include <libft.h>
#include <validate.h>
#include <keycodes.h>
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <constants.h>
#include <rotate_vec.h>
#include <random.h>
#include <hit_objs.h>

int	clip_colour(double c)
{
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return ((int)c);
}

int	rgb_to_int(t_colour c)
{
	int	rgb;

	rgb = clip_colour(c.x);
	rgb = (rgb << 8) + clip_colour(c.y);
	rgb = (rgb << 8) + clip_colour(c.z);
	return (rgb);
}

t_colour	get_ray_luminosity(t_data img, t_object obj, t_ray r)
{
	t_colour c = {0, 0, 0};
	t_colour specular = {255, 255, 255};

	c = plus_vec(c, mult3(obj.colour, img.ambient.brightness));
	if (img.light.brightness == 0)
		return (c);
	c = plus_vec(c, mult3(obj.colour, img.light.brightness * dot(r.direction, obj.normal_to_surface)));
	c = plus_vec(c, mult3(specular, pow(img.light.brightness * dot(obj.normal_to_surface, normalize(plus_vec(r.direction, min_vec(img.camera.view_point, obj.intersection)))), 4 * len3(min_vec(img.light.coordinates, obj.intersection)))));
	return (c);
}


t_colour	cast_ray(t_list **head, t_ray r, t_data img, t_object obj)
{
	t_list	*elem;
	double	t;

	elem = *head;
	t = -1;
	while (elem != NULL)
	{
		if (elem->type == 's')
			t = hit_sphere(((t_sphere *) elem->content), r);
		else if (elem->type == 'p')
			t = hit_plane(((t_plane *) elem->content), r);
		else if (elem->type == 'c')
			t = hit_cylinder(((t_cylinder *) elem->content), r);
		if (t > 0)
		{
			img.light.brightness = 0;
			return (get_ray_luminosity(img, obj, r));
		}
		elem = elem->next;
	}
	return (get_ray_luminosity(img, obj, r));
}

t_colour ray_color(t_ray r, t_list **head, t_data img) {
	double		distance;
	double		t;
	t_list		*elem;
	t_list		*hit_elem;
	t_object	obj;

	hit_elem = NULL;
	distance = DBL_MAX;
	elem = *head;
	t = -1;
	while (elem != NULL) {
		if (elem->type == 's')
			t = hit_sphere(((t_sphere *) elem->content), r);
		else if (elem->type == 'p')
			t = hit_plane(((t_plane *) elem->content), r);
		else if (elem->type == 'c')
		{
			t = hit_cylinder(((t_cylinder *) elem->content), r);
//			if (t > 0)
//				return (((t_cylinder *) elem->content)->colour);
		}
		if (t >= 0 && t < distance)
		{
			distance = t;
			t = -1;
			hit_elem = elem;
		}
		elem = elem->next;
	}
	if (hit_elem != NULL) {

		if (hit_elem->type == 's')
		{
			obj.coordinates = ((t_sphere *) hit_elem->content)->coordinates;
			obj.colour = ((t_sphere *) hit_elem->content)->colour;
		}
		else if (hit_elem->type == 'p')
		{
			obj.coordinates = ((t_plane *) hit_elem->content)->coordinates;
			obj.colour = ((t_plane *) hit_elem->content)->colour;
		}
		else if (hit_elem->type == 'c')
		{
			obj.coordinates = ((t_cylinder *) hit_elem->content)->coordinates;
			obj.colour = ((t_cylinder *) hit_elem->content)->colour;
		}

		obj.intersection = plus_vec(r.origin, mult3(r.direction, distance));
		obj.normal_to_surface = normalize(min_vec(obj.intersection, ((t_sphere *) hit_elem->content)->coordinates));
		r.origin = plus_vec(obj.intersection,mult3(obj.normal_to_surface,1e-5));
		r.direction = normalize(min_vec(img.light.coordinates, r.origin));
		return (cast_ray(head, r, img, obj));
	}
	t_colour c = {0, 0, 0};
	return (c);
}

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

#include <fcntl.h>
#include <unistd.h>
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
