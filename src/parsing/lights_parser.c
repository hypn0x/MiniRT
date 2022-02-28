/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:41 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/18 14:02:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <types.h>
#include <parse_utils.h>

int	add_ambient(char *line, t_ambient *A)
{
	char		*word;

	if (A->brightness != -1)
		return (parsing_error(NULL, "A: cannot be defined more than once"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(A->brightness)))
		return (parsing_error(NULL, "A: brightness is invalid"));
	if (parse_vec3(&line, &(A->colour)))
		return (parsing_error(NULL, "A: colour is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(NULL, "A: Garbage at EOL"));
	return (0);
}

int	add_camera(char *line, t_camera *C)
{
	char		*word;

	if (C->fov != -1)
		return (parsing_error(NULL, "C: cannot be defined more than once"));
	if (parse_vec3(&line, &(C->view_point))
		|| parse_vec3(&line, &(C->orientation)))
		return (parsing_error(NULL, "C: viewpoint or orientation are invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(C->fov)))
		return (parsing_error(NULL, "C: fov is invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(NULL, "C: Garbage at EOL"));
	return (0);
}

int	add_light(char *line, t_list **L)
{
	char		*word;
	t_list		*elem;
	t_light		*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (parsing_error(light, "Malloc failure."));
	if (parse_vec3(&line, &(light->coordinates)))
		return (parsing_error(NULL, "L: coordinates are invalid"));
	word = chop_word(&line, ft_isspace);
	if (ft_atof(word, &(light->brightness)))
		return (parsing_error(NULL, "L: brightness is invalid"));
	if (parse_vec3(&line, &(light->colour)))
		return (parsing_error(NULL, "L: colours are invalid"));
	skip_spaces(&line);
	if (*line)
		return (parsing_error(NULL, "Error parsing L. Garbage at EOL."));
	elem = ft_lstlast(*L);
	if (elem == NULL)
		*L = ft_lstnew(light);
	else
		elem->next = ft_lstnew(light);
	return (0);
}
