/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xb1n4r <wubbalubba@dub.dub>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:42:56 by 0xb1n4r           #+#    #+#             */
/*   Updated: 2022/02/28 16:59:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <types.h>
#include <keycodes.h>

//mlx_destroy_display(data->mlx); Linux variant

int	ft_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->mlx);
	ft_lstclear(data->objects, free);
	ft_lstclear(&(data->light), free);
	free(data->objects);
	exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == K_ESC)
		ft_exit(data);
	return (0);
}
