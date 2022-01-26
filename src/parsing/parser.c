/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:49 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 23:34:52 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "parsing/parse_utils.h"
#include "parsing/objects_parser.h"
#include "parsing/lights_parser.h"

int	parse_line(char *line, t_list **head)
{
	int	ret;

	ret = 1;
	if (line[0] == 'A' && ft_isspace(line[1]))
		ret = add_ambient(line + 1, head);
	else if (line[0] == 'C' && ft_isspace(line[1]))
		ret = add_camera(line + 1, head);
	else if (line[0] == 'L' && ft_isspace(line[1]))
		ret = add_light(line + 1, head);
	else if (!ft_strncmp("sp", line, 2) && ft_isspace(line[2]))
		ret = add_sphere(line + 2, head);
	else if (!ft_strncmp("pl", line, 2) && ft_isspace(line[2]))
		ret = add_plane(line + 2, head);
	else if (!ft_strncmp("cy", line, 2) && ft_isspace(line[2]))
		ret = add_cylinder(line + 2, head);
	return (ret);
}

int	check_ext(const char *filename)
{
	char	*dot;

	dot = ft_strchr(filename, '.');
	if (!dot || dot == filename)
		return (1);
	return (ft_strncmp(".rt", dot, 4));
}

int	open_file(char *filename)
{
	int	fd;

	if (check_ext(filename))
	{
		ft_printf(2, "Error\nWrong file type : %s\n", filename);
		exit (EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Error\nThe scene doesn't exist : %s\n", filename);
		exit (EXIT_FAILURE);
	}
	return (fd);
}

t_list	**parser(char *filename)
{
	char	*line;
	t_list	**head;
	int		fd;

	fd = open_file(filename);
	head = malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (*line)
		{
			if (parse_line(line, head))
			{
				ft_printf(2, "Error\nCould not parse the file");
				ft_lstclear(head, free);
				free(head);
				free(line);
				close(fd);
				exit (EXIT_FAILURE);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (head);
}
