/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:19:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/22 18:03:23 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
//#include <mlx.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bbp;
	int		line_len;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bbp / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "Hello MiniRT!");
	img.img = mlx_new_image(mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bbp, &img.line_len, &img.endian);
	for (int i = 0; i < 800; i++)
		for (int j = 0; j < 800; j++)
			my_mlx_pixel_put(&img, i, j, 0xFFFF0000 + i * j + i * j);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
