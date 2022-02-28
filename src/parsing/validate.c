/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:55 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/28 15:19:24 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>
#include <libft.h>
#include <validate_utils.h>

static int	check_objects_values(t_list *head)
{
	while (head != NULL)
	{
		if (head->type == 's')
			if (check_colour(((t_sphere *)head->content)->colour))
				return (1);
		if (head->type == 'p')
			if (check_colour(((t_plane *)head->content)->colour)
				|| check_orientation(((t_plane *)head->content)->orientation))
				return (2);
		if (head->type == 'c')
			if (check_colour(((t_cylinder *)head->content)->colour)
				|| check_orientation
				(((t_cylinder *)head->content)->orientation))
				return (2);
		if (head->type == 't')
			if (check_colour(((t_triangle *)head->content)->colour))
				return (2);
		head = head->next;
	}
	return (0);
}

int	check_light(t_list *elem)
{
	t_light *light;

	while (elem)
	{
		light = elem->content;
		if (check_brightness(light->brightness)
			   || check_colour(light->colour))
			return (1);
		elem = elem->next;
	}
	return (0);
}

int	check_list_values(t_list *head, t_ambient *A, t_list *L, t_camera *C)
{
	if (A->brightness == -1)
		A->brightness = 0;
	return (check_brightness(A->brightness)
		|| check_colour(A->colour)
		|| check_orientation(C->orientation)
		|| check_range(C->fov, 0.0f, 180.0f)
		|| check_light(L)
		|| check_objects_values(head));
}
