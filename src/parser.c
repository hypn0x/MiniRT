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

int check_ext(const char *filename)
{
    char *dot;

    dot = ft_strchr(filename, '.');
    if(!dot || dot == filename)
        return (1);
    if ((ft_strncmp(".rt", dot, 3) == 0) && ft_strlen(dot) == 3)
        return (0);
    else
        return (1);
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
    if (check_ext(argv[1]))
    {
        ft_printf(1, "Error\nWrong file type : %s\n", argv[1]);
        free(head);
        exit (EXIT_FAILURE);
    }
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
    {
        ft_printf(1, "Error\nThe scene doesn't exist : %s\n", argv[1]);
        free(head);
        exit (EXIT_FAILURE);
    }
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
