/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:45 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 23:34:47 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <types.h>
#include <parse_utils.h>

int	add_sphere(char *line, t_list **head)
{
	t_sphere	*elem;
	char		*word;

	elem = malloc(sizeof(t_sphere));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	parse_vec3(&line, &(elem->coordinates));
	word = chop_word(&line, ft_isspace);
	elem->diameter = ft_atof(word);
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing sp. Unknown char at EOL."));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 's';
	return (0);
}

int	add_plane(char *line, t_list **head)
{
	t_plane	*elem;

	elem = malloc(sizeof(t_plane));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	parse_vec3(&line, &(elem->coordinates));
	parse_vec3(&line, &(elem->orientation));
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing pl. Unknown char at EOL."));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'p';
	return (0);
}

int	add_cylinder(char *line, t_list **head)
{
	t_cylinder	*elem;
	char		*word;

	elem = malloc(sizeof(t_cylinder));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	parse_vec3(&line, &(elem->coordinates));
	parse_vec3(&line, &(elem->orientation));
	word = chop_word(&line, ft_isspace);
	elem->diameter = ft_atof(word);
	word = chop_word(&line, ft_isspace);
	elem->height = ft_atof(word);
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing cy. Unknown char at EOL."));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'c';
	return (0);
}
