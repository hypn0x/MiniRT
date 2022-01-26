/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/26 14:51:34 by 0xb1n4r          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <mlx.h>
#include <libft.h>
//#include <mlx.h>
#include <keycodes.h>
#include <types.h>
#include <op_vec_double.h>
#include <op_vec.h>

int	hit_sphere(const t_point center, double radius, t_ray r) {
	t_vec3 oc = min_vec(r.origin, center);
	double a = dot(r.direction, r.direction);
	double b = 2.0 * dot(oc, r.direction);
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

int ray_color(t_ray r)
{
	t_point sphere = {0, 0, -1};
	if (hit_sphere(sphere, 0.5, r))
		return (0xFFFFFF);
	t_vec3 unit_direction = unit_vector(r.direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	return (int)((1.0 - t) * 0xFFFFFF + t * 0xFF0000);
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc == 2)
    {
        if (!parser(argc, argv))
            ft_printf(1, "Error\nFile scene corrupted\n");
    }
    else
    {
        ft_printf(1, "Usage: ./miniRT (scene)\n");
        return (0);
    }
    const double aspect_ratio = 16.0 / 9.0;
    const int img_width = 480;
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
            img.addr[px++] = ray_color(ray);
        }
    }
    mlx_hook(img.mlx_win, 17, 1L, ft_exit, &img);
    mlx_hook(img.mlx_win, 2, 1L, key_hook, &img);
    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
