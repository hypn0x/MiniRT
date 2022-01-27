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

int	add_ambient(char *line, t_list **head)
{
	t_ambient	*elem;
	char		*word;

	if (check_exist('A', head))
		return (parsing_error(NULL, "A: cannot be defined more than once"));
	elem = malloc(sizeof(t_ambient));
	if (!elem)
		return (parsing_error(elem, "Malloc failure"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(elem->brightness)))
		return (parsing_error(elem, "A: brightness is invalid"));
	if (parse_vec3(&line, &(elem->colour)))
		return (parsing_error(elem, "A: colour is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "A: Garbage at EOL"));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure"));
	(*head)->content = elem;
	(*head)->type = 'A';
	return (0);
}

int	add_camera(char *line, t_list **head)
{
	t_camera	*elem;
	char		*word;

	if (check_exist('C', head))
		return (parsing_error(NULL, "C: cannot be defined more than once"));
	elem = malloc(sizeof(t_camera));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	if (parse_vec3(&line, &(elem->view_point)) || parse_vec3(&line, &(elem->orientation)))
		return (parsing_error(elem, "C: viewpoint or orientation are invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(elem->fov)))
		return (parsing_error(elem, "C: fov is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "C: Garbage at EOL"));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'C';
	return (0);
}

int	add_light(char *line, t_list **head)
{
	t_light		*elem;
	char		*word;

	if (check_exist('L', head))
		return (parsing_error(NULL, "L: cannot be defined more than once"));
	elem = malloc(sizeof(t_light));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	if (parse_vec3(&line, &(elem->coordinates)))
		return (parsing_error(elem, "L: coordinates are invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(elem->brightness)))
		return (parsing_error(elem, "L: brightness is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing L. Garbage at EOL."));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'L';
	return (0);
}
