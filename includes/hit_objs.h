/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:33:18 by                   #+#    #+#             */
/*   Updated: 2022/02/26 12:28:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_OBJS_H
# define HIT_OBJS_H

# include <types.h>

t_colour	cast_ray(t_ray r, t_data img, t_object obj);
float		hit_sphere(const t_sphere *sphere, t_ray r);
float		hit_plane(t_plane *plane, t_ray r);
float		hit_cylinder(t_cylinder *cylinder, t_ray r);
void		create_caps(t_cylinder *cylinder);
void		check_t(float *t, t_cylinder *cylinder, t_ray ray);
float		hit_triangle(t_triangle *triangle, t_ray ray);

#endif //HIT_OBJS_H
