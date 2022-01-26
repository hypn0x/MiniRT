/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:41 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 23:34:45 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <types.h>
#include <parse_utils.h>

int	parsing_error(void *elem, char *error)
{
	ft_printf(2, "%s\n", error);
	free(elem);
	return (1);
}

int	add_ambient(char *line, t_list **head)
{
	t_ambient	*elem;
	char		*word;

	if (check_exist('A', head))
		return (1);
	elem = malloc(sizeof(t_ambient));
	if (!elem)
		return (1);
	word = chop_word(&line, ft_isspace);
	elem->brightness = atof(word);
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing A. Unknown char at EOL."));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'A';
	return (0);
}

int	add_camera(char *line, t_list **head)
{
	t_camera	*elem;
	char		*word;

	if (check_exist('C', head))
		return (1);
	elem = malloc(sizeof(t_camera));
	if (!elem)
		return (1);
	//todo: replace with custom atof && error checking
	parse_vec3(&line, &(elem->view_point));
	parse_vec3(&line, &(elem->orientation));
	word = chop_word(&line, ft_isspace);
	elem->fov = ft_atoi(word);
	skip_spaces(&line);
	if (*line) // still some content at the end of line
		return (1);
	if (new_elem(head))
		return (1);
	(*head)->content = elem;
	(*head)->type = 'C';
	return (0);
}

int	add_light(char *line, t_list **head)
{
	t_light		*elem;
	char		*word;

	if (check_exist('L', head))
		return (1);
	elem = malloc(sizeof(t_light));
	if (!elem)
		return (1);
	//todo: replace with custom atof && error checking
	parse_vec3(&line, &(elem->coordinates));
	word = chop_word(&line, ft_isspace);
	elem->brightness = atof(word);
	skip_spaces(&line);
	if (*line) // still some content at the end of line
		return (1);
	if (new_elem(head))
		return (1);
	(*head)->content = elem;
	(*head)->type = 'L';
	return (0);
}
