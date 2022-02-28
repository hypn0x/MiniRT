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
#include <float.h>
#include <colors.h>
#include <random.h>

void	format_lights(t_data *img)
{
	t_list	*elem;
	t_light	*light;

	img->ambient.colour = mult3(img->ambient.colour,
			img->ambient.brightness / 255.0f);
	elem = img->light;
	while (elem)
	{
		light = elem->content;
		light->colour = mult3(light->colour, light->brightness / 255.0f);
		elem = elem->next;
	}
}

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
	// todo: fix case where cross prod = 0
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
	// top_left
	ray.direction = normalize(top_left);
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = create_obj(hit_elem, ray, img, distance);
	// top_right
	ray.direction = normalize(plus_vec(top_left, img.horizontal));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = plus_vec(val, create_obj(hit_elem, ray, img, distance));
	// bottom_left
	ray.direction = normalize(plus_vec(top_left, img.vertical));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = plus_vec(val, create_obj(hit_elem, ray, img, distance));
	// bottom_right
	ray.direction = normalize(plus_vec(plus_vec(top_left, img.vertical), img.horizontal));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	val = plus_vec(val, create_obj(hit_elem, ray, img, distance));
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

t_colour	supersample_px(t_ray ray, t_data img)
{
	int	i;
	t_colour	c;
	t_list		*hit_elem;
	float		distance;
	i = -1;

	c = new_vec(0.0f, 0.0f, 0.0f);
	while (++i < 4)
	{
		ray.direction = normalize(plus_vec(plus_vec(ray.direction,
			mult3(img.vertical, ft_rand(0))), mult3(img.horizontal, ft_rand(0))));
		distance = DBL_MAX;
		hit_elem = get_hit_elem(ray, img.objects, &distance);
		c = plus_vec(c, create_obj(hit_elem, ray, img, distance));
	}
	return (div3(c, 4));
}

void *new_light(void *content)
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

	img.light = ft_lstmap(img.light, new_light, free);
	if (SUPERSAMPLING)
		v1 = get_mean_pixel(ray, img);
	top_left = ray.direction;
	ray.direction = normalize(plus_vec(plus_vec(ray.direction,
			mult3(img.vertical, 0.5f)), mult3(img.horizontal, 0.5f)));
	distance = DBL_MAX;
	hit_elem = get_hit_elem(ray, img.objects, &distance);
	v2 = create_obj(hit_elem, ray, img, distance);
	ray.direction = top_left;
	if (SUPERSAMPLING && is_px_diff(v1, v2))
		return (rgb_to_int(div3(plus_vec(v1, plus_vec(v2, supersample_px(ray, img))), 3)));
	if (SUPERSAMPLING)
		return (rgb_to_int(div3(plus_vec(v1, v2), 2)));
	return (rgb_to_int(v1));
}

#include <pthread.h>

typedef struct s_thread
{
	int		i;
	int		start_y;
	t_data	*img;
}	t_thread;

#include <stdio.h>


void	*thread_loop(void *ptr)
{
	t_thread	*dt;
	int		y;
	int		x;
	int		px;
	t_ray	ray;
	t_vec3	horiz;

	dt = ptr;
	t_data *img = dt->img;
	horiz = mult3(img->horizontal, IMG_W);
	y = dt->start_y - 1;
	px = dt->start_y * IMG_W;
	ray.origin = img->camera.view_point;
	ray.direction = plus_vec(img->top_left_corner, mult3(img->vertical, (float)y));
	while (++y < (dt->i + 1) * (IMG_H / 12))
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
//	ft_lstclear(&(img->light), free);
	return (NULL);
}

void	multithreading(t_data *img)
{
	int	i;
	t_thread *dt = malloc(sizeof(t_thread) * 12);
	pthread_t *t = malloc(sizeof(pthread_t) * 12);

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

void	create_img(t_data *img)
{
	int		y;
	int		x;
	int		px;
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
}
