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

// todo: error checking once ft_atof is fixed
int	add_ambient(char *line, t_list **head)
{
	t_ambient	*elem;
	char		*word;

	if (check_exist('A', head))
		return (parsing_error(NULL,
				"Object A cannot be defined more than one time."));
	elem = malloc(sizeof(t_ambient));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
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
		return (parsing_error(NULL,
				"Object C cannot be defined more than one time."));
	elem = malloc(sizeof(t_camera));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	parse_vec3(&line, &(elem->view_point));
	parse_vec3(&line, &(elem->orientation));
	word = chop_word(&line, ft_isspace);
	elem->fov = ft_atoi(word);
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing C. Unknown char at EOL."));
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
		return (parsing_error(NULL,
				"Object L cannot be defined more than one time."));
	elem = malloc(sizeof(t_light));
	if (!elem)
		return (parsing_error(elem, "Malloc failure."));
	parse_vec3(&line, &(elem->coordinates));
	word = chop_word(&line, ft_isspace);
	elem->brightness = atof(word);
	skip_spaces(&line);
	if (*line)
		return (parsing_error(elem, "Error parsing L. Unknown char at EOL."));
	if (new_elem(head))
		return (parsing_error(elem, "Malloc failure."));
	(*head)->content = elem;
	(*head)->type = 'L';
	return (0);
}
