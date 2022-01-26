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
		return (1);
	//todo: replace with custom atof && error checking
	parse_vec3(&line, &(elem->coordinates));
	word = chop_word(&line, ft_isspace);
	elem->diameter = atof(word);
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line) // still some content at the end of line
		return (1);
	if (new_elem(head))
		return (1);
	(*head)->content = elem;
	(*head)->type = 's'; // using s for sphere instead of sp
	return (0);
}

int	add_plane(char *line, t_list **head)
{
	t_plane	*elem;

	elem = malloc(sizeof(t_plane));
	if (!elem)
		return (1);
	//todo: replace with custom atof && error checking
	parse_vec3(&line, &(elem->coordinates));
	parse_vec3(&line, &(elem->orientation));
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line) // still some content at the end of line
		return (1);
	if (new_elem(head))
		return (1);
	(*head)->content = elem;
	(*head)->type = 'p'; // using s for sphere instead of sp
	return (0);
}

int	add_cylinder(char *line, t_list **head)
{
	t_cylinder	*elem;
	char		*word;

	elem = malloc(sizeof(t_cylinder));
	if (!elem)
		return (1);
	//todo: replace with custom atof && error checking
	parse_vec3(&line, &(elem->coordinates));
	parse_vec3(&line, &(elem->orientation));
	word = chop_word(&line, ft_isspace);
	elem->diameter = atof(word);
	word = chop_word(&line, ft_isspace);
	elem->height = atof(word);
	parse_vec3(&line, &(elem->colour));
	skip_spaces(&line);
	if (*line) // still some content at the end of line
		return (1);
	if (new_elem(head))
		return (1);
	(*head)->content = elem;
	(*head)->type = 'c'; // using s for sphere instead of sp
	return (0);
}
