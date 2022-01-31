/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/31 13:32:12 by                  ###   ########.fr       */
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

double	solve_quadratic(double a, double b, double c)
{
	double	d;
	double	t0;
	double	t1;
	double	q;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	if (d == 0)
		return (-0.5 * b / a);
	if (b > 0)
		q = -0.5 * (b + sqrt(d));
	else
		q = -0.5 * (b - sqrt(d));
	t0 = q / a;
	t1 = c / q;
	if (t0 > t1)
	{
		q = t1;
		t1 = t0;
		t0 = q;
	}
	if (t0 < 0)
		return (t1);
	return (t0);
}

double	hit_sphere(const t_sphere *sphere, t_ray r)
{
	t_vec3	oc;
	double	radius;
	double	a;
	double	b;
	double	c;

	radius = sphere->diameter / 2;
	oc = min_vec(r.origin, sphere->coordinates);
	a = dot(r.direction, r.direction);
	b = 2.0 * dot(r.direction, oc);
	c = dot(oc, oc) - radius * radius;
	return (solve_quadratic(a, b, c));
}

int	rgb_to_int(t_colour c)
{
	int	rgb;

	rgb = (int) c.x;
	rgb = (rgb << 8) + (int) c.y;
	rgb = (rgb << 8) + (int) c.z;
	return (rgb);
}

int	cast_ray(t_light L, t_ambient A, t_vec3 hit_point, t_sphere *sp)
{
	t_vec3	normal;
	t_vec3	ld;
	double	intensity;
	int		ret;

	normal = min_vec(sp->coordinates, hit_point);
	ld = normalize(min_vec(L.coordinates, hit_point));
//   hit_point = normalize(hit_point);
	normal = normalize(normal);
	//TODO maybe multiply by light ratio * L.brightness;
	intensity = dot(normal, ld) * A.brightness;
	ret = rgb_to_int(mult3(sp->colour, intensity));
	if (ret < 0)
		ret = 0;
	return (ret);
}

int	ray_color(t_ray r, t_list **head, t_light L, t_ambient A)
{
	double	distance;
	double	t;
	t_list	*elem;
	t_list	*hit_elem;

	hit_elem = NULL;
	distance = DBL_MAX;
	elem = *head;
	while (elem != NULL)
	{
		if (elem->type == 's')
		{
			t = hit_sphere(((t_sphere *) elem->content), r);
			if (t >= 0 && t < distance)
			{
				distance = t;
				hit_elem = elem;
			}
		}
		elem = elem->next;
	}
	if (hit_elem != NULL)
		return (cast_ray(L, A, plus_vec(r.origin, mult3(r.direction, distance)), hit_elem->content));
	return (0);
}

t_vec3	rotate_y_axis(double angle, t_vec3 v)
{
	t_vec3	r;

	r.x = v.x * cos(angle) + v.z * sin(angle);
	r.y = v.y;
	r.z = -v.x * sin(angle) + v.z * cos(angle);
	return (r);
}

t_vec3	rotate_x_axis(double angle, t_vec3 v)
{
	t_vec3	r;

	r.x = v.x;
	r.y = v.y * cos(angle) - v.z * sin(angle);
	r.z = v.y * sin(angle) + v.z * cos(angle);
	return (r);
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
	img->horizontal = mult3(rotate_y_axis(M_PI_2, img->camera.orientation), img->viewport_width);
	img->vertical = mult3(rotate_x_axis(M_PI_2, img->camera.orientation), img->viewport_height);
	img->top_left_corner = plus_vec(plus_vec(min_vec(img->camera.view_point, div3(img->horizontal, 2)), div3(img->vertical, 2)), img->camera.orientation);
	mlx_hook(img->mlx_win, 17, 1L, ft_exit, img);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
}

void	create_img(t_list **objects, t_data	*img)
{
	int		y;
	int		x;
	t_ray	ray;
	int		px;

	y = -1;
	ray.origin = img->camera.view_point;
	px = 0;
	while (++y < IMG_H)
	{
		x = -1;
		while (++x < IMG_W)
		{
			ray.direction = min_vec(plus_vec(plus_vec(img->top_left_corner,
							mult3(img->horizontal, ((double) x + .5) / IMG_W)),
						mult3(img->vertical, -((double) y + .5) / IMG_H)),
					ray.origin);
			img->addr[px++] = ray_color(ray, objects, img->light, img->ambient);
		}
	}
}

int	main(int argc, char **argv)
{
	t_list		**objects;
	t_data		img;

	if (argc != 2)
		return (ft_printf(2, "Usage: ./miniRT (scene)\n"));
	objects = parser(argv[1], &(img.camera), &(img.light), &(img.ambient));
	if (objects == NULL)
		return (ft_printf(2, "Error\nFile scene corrupted\n"));
	else if (check_list_values(*objects))
	{
		ft_lstclear(objects, free);
		free(objects);
		return (ft_printf(2, "Error\nInvalid value in scene\n"));
	}
	init_image(&img);
	create_img(objects, &img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
}
