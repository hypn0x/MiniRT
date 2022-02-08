/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:04:13 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/07 20:49:31 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by segransm on 1/26/22.
//

#ifndef TYPES_H
# define TYPES_H

# include <libft.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_point;
typedef t_vec3	t_colour;

typedef struct s_ray
{
	t_vec3	direction;
	t_point	origin;
}	t_ray;

typedef struct s_ambient
{
	double		brightness;
	t_colour	colour;
}	t_ambient;

typedef struct s_camera
{
	t_point	view_point;
	t_vec3	orientation;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_point	coordinates;
	double	brightness;
}	t_light;

typedef struct s_sphere
{
	t_point		coordinates;
	double		diameter;
	t_colour	colour;
}	t_sphere;

typedef struct s_plane
{
	t_point		coordinates;
	t_vec3		orientation;
	t_colour	colour;
}	t_plane;

typedef struct s_cylinder
{
	t_point		coordinates;
	t_vec3		orientation;
	double		diameter;
	double		height;
	t_colour	colour;
}	t_cylinder;

typedef struct s_object
{
	t_point		coordinates;
	t_colour	colour;
	t_vec3		normal_to_surface;
	t_vec3		intersection;
}	t_object;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bbp;
	int			line_len;
	int			endian;
	double		viewport_width;
	double		viewport_height;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_point		top_left_corner;
	t_camera	camera;
	t_light		light;
	t_ambient	ambient;
}	t_data;

int	ft_exit(t_data *data);
int	key_hook(int keycode, t_data *data);

#endif //TYPES_H
