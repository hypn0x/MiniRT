/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:34:49 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/26 10:58:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "parsing/objects_parser.h"
#include "parsing/lights_parser.h"
#include <parse_utils.h>

int	parse_line(char *line, t_list **head, t_camera *C, t_list **L, t_ambient *A)
{
	if (line[0] == 'A' && ft_isspace(line[1]))
		return (add_ambient(line + 1, A));
	if (line[0] == 'C' && ft_isspace(line[1]))
		return (add_camera(line + 1, C));
	if (line[0] == 'L' && ft_isspace(line[1]))
		return (add_light(line + 1, L));
	if (!ft_strncmp("sp", line, 2) && ft_isspace(line[2]))
		return (add_sphere(line + 2, head));
	if (!ft_strncmp("pl", line, 2) && ft_isspace(line[2]))
		return (add_plane(line + 2, head));
	if (!ft_strncmp("cy", line, 2) && ft_isspace(line[2]))
		return (add_cylinder(line + 2, head));
	if (!ft_strncmp("tr", line, 2) && ft_isspace(line[2]))
		return (add_triangle(line +2, head));
	return (1);
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

void	remove_comments(char *line)
{
	while (*line)
	{
		if (*line == '#')
		{
			*line = 0;
			return ;
		}
		line++;
	}
}

t_list	**parser(char *filename, t_camera *C, t_list **L, t_ambient *A)
{
	char	*line;
	t_list	**head;
	int		fd;

	C->fov = -1;
	A->brightness = -1;
	fd = open_file(filename);
	head = malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	*head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		remove_comments(line);
		skip_spaces(&line);
		if (*line)
		{
			if (parse_line(line, head, C, L, A))
			{
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
