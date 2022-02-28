/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:45 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/26 12:16:32 by                  ###   ########.fr       */
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
	if (parse_vec3(&line, &(elem->coordinates)))
		return (parsing_error(elem, "sp: coordinates are invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(elem->diameter)))
		return (parsing_error(elem, "sp: diameter is invalid"));
	if (parse_vec3(&line, &(elem->colour)))
		return (parsing_error(elem, "sp: colour is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "sp: Garbage at EOL"));
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
	if (parse_vec3(&line, &(elem->coordinates))
		|| parse_vec3(&line, &(elem->orientation))
		|| parse_vec3(&line, &(elem->colour)))
		return (parsing_error(elem,
				"pl: coordinates, orientation or colour are invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "pl: Garbage at EOL"));
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
	if (parse_vec3(&line, &(elem->coordinates))
		|| parse_vec3(&line, &(elem->orientation)))
		return (parsing_error(elem, "cy: coordinates/orientation is invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(elem->diameter)))
		return (parsing_error(elem, "cy: diameter is invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(elem->height)))
		return (parsing_error(elem, "cy: height is invalid"));
	if (parse_vec3(&line, &(elem->colour)))
		return (parsing_error(elem, "cy: colour is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "cy: Garbage at EOL"));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'c';
	return (0);
}

int	add_triangle(char *line, t_list **head)
{
	t_triangle 	*elem;

	elem = malloc(sizeof(t_triangle));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	if (parse_vec3(&line, &(elem->a)) || parse_vec3(&line, &(elem->b))
		|| parse_vec3(&line, &elem->c))
		return (parsing_error(elem, "tr: a/b/c is invalid"));
	if (parse_vec3(&line, &(elem)->colour))
		return (parsing_error(elem, "tr: invalid colour"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "tr: Garbage at EOL"));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure"));
	(*head)->content = elem;
	(*head)->type = 't';
	return (0);
}
