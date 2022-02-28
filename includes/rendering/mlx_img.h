//
// Created by Hajar Sabir on 2/8/22.
//

#ifndef MLX_IMG_H
# define MLX_IMG_H

# include <mlx.h>
# include <types.h>

void		init_image(t_data *img);
int			is_px_diff(t_colour c1, t_colour c2);
void		create_img(t_data	*img);
void		format_lights(t_data *img);
void		multithreading(t_data *img);
void 		*new_light(void *content);
int			get_pixel_value(t_ray ray, t_data img);
t_colour	supersample_px(t_ray ray, t_data img);

#endif //MLX_IMG_H
