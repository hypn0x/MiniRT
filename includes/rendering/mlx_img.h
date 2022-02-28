/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:40:17 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/28 21:40:19 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Hajar Sabir on 2/8/22.
//

#ifndef MLX_IMG_H
# define MLX_IMG_H

# include <mlx.h>
# include <types.h>

void		init_image(t_data *img);
void		img_loop(t_data *img);
void		format_lights(t_data *img);
void		multithreading(t_data *img);
int			get_pixel_value(t_ray ray, t_data img);
t_colour	supersample_px(t_ray ray, t_data img);

#endif //MLX_IMG_H
