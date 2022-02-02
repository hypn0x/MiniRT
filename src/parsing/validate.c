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
		if (head->type == 'C')
			if (check_orientation(((t_camera *)head->content)->orientation)
				|| check_range_double(
					((t_camera *)head->content)->fov, 0.0, 180.0))
				return (2);
		if (head->type == 'L')
		{
			if (((t_light *)head->content)->brightness == -1)
				((t_light *)head->content)->brightness = 0;
			if (check_brightness(((t_light *)head->content)->brightness))
				return (3);
		}
	head = head->next;
	}
	return (0);
}

int	check_list_values(t_list *head, t_ambient *A, t_light *L, t_camera *C)
{
	if (A->brightness == -1)
		A->brightness = 0;
	if (L->brightness == -1)
		L->brightness = 0;
	return (check_brightness(A->brightness)
		|| check_colour(A->colour)
		|| check_brightness(L->brightness)
		|| check_orientation(C->orientation)
		|| check_range_double(C->fov, 0.0, 180.0)
		|| check_objects_values(head));
}
