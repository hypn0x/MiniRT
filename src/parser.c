//
// Created by segransm on 1/25/22.
//

#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <types.h>
#include <parse_utils.h>
#include <objects_parser.h>
#include <lights_parser.h>

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

t_list	**parser(int argc, char **argv)
{
	char	*line;
	t_list	**head;
	int		fd;

	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	if (argc < 2)
		return (NULL);
	head = malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line)
		{
			ft_printf(2, "%s\n", line);
			if (parse_line(line, head))
			{
				// todo: maybe custom error message depending on the error
				ft_printf(2, "Error\nCould not parse the file");
				return (NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (head);
}
