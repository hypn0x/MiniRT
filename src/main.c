/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/27 14:22:30 by hsabir           ###   ########.fr       */
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

#include <math.h>

double	solve_quadratic(double a, double b, double c)
{
	double d;
	double t0;
	double t1;
	double q;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	if (d == 0)
		return (- 0.5 * b / a);

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

int rgb_to_int(t_colour c)
{
	int rgb;

	rgb = (int)c.x;
	rgb = (rgb << 8) + (int)c.y;
	rgb = (rgb << 8) + (int)c.z;
	return (rgb);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//const char *shades = ".:!*oe&#%@";
//
//double light[3] = { 60, 60, -60 };
//
//void normalize(t_vec3 v)
//{
//    double len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
//    if (len > 0.0)
//        v.x /= len; v.y /= len; v.z /= len;
//}
//
////double dot(double *x, double *y)
////{
////    double d = x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
////    if (d < 0)
////        return (-d);
////    else
////        return (0);
////}
//
//void draw_sphere(double R, double k, double ambient)
//{
//    int i, j, intensity;
//    double b;
//    // Cross product
//    double vec[3];
//    double x, y;
//    for (i = (-R); i <= (R); i++) {
//        x = i + .5;
//        for (j = (-2 * R); j <= (2 * R); j++) {
//            y = j / 2. + .5;
//            if (x * x + y * y <= R * R) {
//                vec[0] = x;
//                vec[1] = y;
//                vec[2] = sqrt(R * R - x * x - y * y);
//                normalize(vec);
//                b = pow(dot(light, vec), k) + ambient;
//                intensity = (1 - b) * (sizeof(shades) - 1);
//                if (intensity < 0)
//                    intensity = 0;
//                if (intensity >= sizeof(shades) - 1)
//                    intensity = sizeof(shades) - 2;
//                putchar(shades[intensity]);
//            }
//            else
//                putchar(' ');
//        }
//        putchar('\n');
//    }
//}

double dot3(t_vec3 a, t_vec3 b)
{
    double d = a.x * b.x + a.y * b.y + a.z * b.z;
    if (d < 0)
        return (-d);
    return (0);
}

int cast_ray(t_light L, t_ambient A, t_vec3 hit_point, t_colour c)
{
    double b;
    t_vec3 ln = unit_vector(L.coordinates);
    hit_point = unit_vector(hit_point);
    b = pow(dot3(ln, hit_point), L.brightness) + A.brightness;
    return (rgb_to_int(mult3(c, (1.0 - b))));
}

int	ray_color(t_ray r, t_list **head)
{
	double distance = DBL_MAX;
	double t;
	t_list *elem;
	t_list *hit_elem = NULL;
    t_light L;
    t_ambient A;

	elem = *head;
	while (elem != NULL)
	{
        if (elem->type == 'L')
            L = *((t_light *)elem->content);
        if (elem->type == 'A')
            A = *((t_ambient *)elem->content);
		if (elem->type == 's')
		{
			t = hit_sphere(((t_sphere *)elem->content), r);
			if (t >= 0 && t < distance)
			{
				distance = t;
				hit_elem = elem;
			}
		}
		elem = elem->next;
	}
	if (hit_elem != NULL)
	{
		return (cast_ray(L, A, mult3(r.direction, distance), ((t_sphere *)hit_elem->content)->colour));
		//return (rgb_to_int(((t_sphere *)hit_elem->content)->colour));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_list 	**head;


	if (argc != 2)
		return (ft_printf(2, "Usage: ./miniRT (scene)\n"));
	head = parser(argv[1]);
	if (head == NULL)
		return (ft_printf(2, "Error\nFile scene corrupted\n"));
	else if (check_list_values(*head))
	{
		ft_lstclear(head, free);
		free(head);
		return (ft_printf(2, "Error\nInvalid value in scene\n"));
	}

    const double aspect_ratio = 16.0 / 9.0;
    const int img_width = 720;
    const int img_height = (int)(img_width / aspect_ratio);
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;

    t_vec3 focal_length = {0, 0, 1};
    t_vec3 origin = {0, 0, 0};
    t_vec3 horizontal = {viewport_width, 0, 0};
    t_vec3 vertical = {0, viewport_height, 0};

    t_vec3 lower_left_corner = min_vec(
            min_vec(min_vec(origin, div3(horizontal, 2)), div3(vertical, 2)),
            focal_length);

    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, img_width, img_width, "Hello MiniRT!");
    img.img = mlx_new_image(img.mlx, img_width, img_width);
    img.addr = (int *)mlx_get_data_addr(img.img, &img.bbp, &img.line_len, &img.endian);
    int px = 0;
    for (int i = 0; i < img_width; i++)
    {
        for (int j = 0; j < img_width; j++)
        {
            double w = (double) i / img_width;
            double h = (double) j / img_height;

            t_ray ray;
            ray.origin = origin;
            ray.direction = min_vec(
                    plus_vec(plus_vec(lower_left_corner, mult3(horizontal, w)),
                             mult3(vertical, h)), origin);
            img.addr[px++] = ray_color(ray, head);
        }
    }
    mlx_hook(img.mlx_win, 17, 1L, ft_exit, &img);
    mlx_hook(img.mlx_win, 2, 1L, key_hook, &img);
    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
