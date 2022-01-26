/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:55 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 23:34:58 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>
#include <libft.h>
#include <validate_utils.h>

static int	check_objects_values(t_list *head)
{
	while (head != NULL)
	{
		if (head->type == 'A')
			if (check_brightness(((t_ambient *)head->content)->brightness)
				|| check_colour(((t_ambient *)head->content)->colour))
				return (1);
		if (head->type == 'C')
			if (check_orientation(((t_camera *)head->content)->orientation)
				|| check_range_double(
					((t_camera *)head->content)->fov, 0.0, 180.0))
				return (2);
		if (head->type == 'L')
			if (check_brightness(((t_light *)head->content)->brightness))
				return (3);
	head = head->next;
	}
	return (0);
}

static int	check_lights_values(t_list *head)
{
	while (head != NULL)
	{
		if (head->type == 's')
			if (check_colour(((t_sphere *)head->content)->colour))
				return (4);
		if (head->type == 'p')
			if (check_colour(((t_plane *)head->content)->colour)
				|| check_orientation(((t_plane *)head->content)->orientation))
				return (5);
		if (head->type == 'c')
			if (check_colour(((t_cylinder *)head->content)->colour)
				|| check_orientation(
					((t_cylinder *)head->content)->orientation))
				return (6);
		head = head->next;
	}
	return (0);
}

int	check_list_values(t_list *head)
{
	return (check_lights_values(head) || check_objects_values(head));
}
