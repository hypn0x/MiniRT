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

static int	parse_object(char *line, t_data *img)
{
	if (line[0] == 'A' && ft_isspace(line[1]))
		return (add_ambient(line + 1, &(img->ambient)));
	if (line[0] == 'C' && ft_isspace(line[1]))
		return (add_camera(line + 1, &(img->camera)));
	if (line[0] == 'L' && ft_isspace(line[1]))
		return (add_light(line + 1, &(img->light)));
	if (!ft_strncmp("sp", line, 2) && ft_isspace(line[2]))
		return (add_sphere(line + 2, img->objects));
	if (!ft_strncmp("pl", line, 2) && ft_isspace(line[2]))
		return (add_plane(line + 2, img->objects));
	if (!ft_strncmp("cy", line, 2) && ft_isspace(line[2]))
		return (add_cylinder(line + 2, img->objects));
	if (!ft_strncmp("tr", line, 2) && ft_isspace(line[2]))
		return (add_triangle(line + 2, img->objects));
	return (1);
}

static int	check_ext(const char *filename)
{
	char	*dot;

	dot = ft_strchr(filename, '.');
	if (!dot || dot == filename)
		return (1);
	return (ft_strncmp(".rt", dot, 4));
}

static int	open_file(char *filename)
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

static int	parse_line(char *line_head, t_data *img)
{
	char	*line;

	line = line_head;
	while (*line)
	{
		if (*line == '#')
			*line = 0;
		line++;
	}
	skip_spaces(&line_head);
	if (*line_head)
	{
		if (parse_object(line_head, img))
		{
			ft_lstclear(img->objects, free);
			free(img->objects);
			free(line_head);
			return (1);
		}
	}
	return (0);
}

void	parser(char *filename, t_data *img)
{
	char	*line;
	int		fd;

	img->light = NULL;
	img->camera.fov = -1;
	img->ambient.brightness = -1;
	fd = open_file(filename);
	img->objects = malloc(sizeof(t_list *));
	if (!img->objects)
		return ;
	*(img->objects) = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, img))
		{
			close(fd);
			exit (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
