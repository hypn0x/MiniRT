//
// Created by segransm on 1/25/22.
//

#include <libgnl.h>
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_vec3
{
  double x;
  double y;
  double z;
} t_vec3;

typedef t_vec3 t_point;
typedef t_vec3 t_colour;

typedef struct s_ambient
{
	double		brightness;
	t_colour	colour;
}	t_ambient;

typedef struct s_camera
{
  t_point	view_point;
  t_vec3	orientation;
  int		fov;
}	t_camera;

typedef struct s_light
{
  t_point	coordinates;
  t_vec3	orientation;
  double	brightness;
//t_colour	colour; TODO: only used in bonus
}	t_light;

typedef struct s_sphere
{
	t_point		coordinates;
	double		diameter;
	t_colour	colour;
}	t_sphere;

typedef struct s_plane
{
	t_point	coordinates;
	t_vec3	orientation;
	t_colour	colour;
}	t_plane;

typedef struct s_cylinder
{
  t_point	coordinates;
  t_vec3	orientation;
  double	diameter;
  double	height;
  t_colour	colour;
}	t_cylinder;

void	skip_spaces(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

int	check_exist(char type, t_list **head)
{
	t_list *elem;

	elem = *head;
	while (elem)
	{
		if (elem->type == type)
			return (1);
		elem = elem->next;
	}
	return (0);
}

int	new_lst(t_list **head)
{
	t_list	*elem;

	elem = ft_lstnew(NULL);
	if (!elem)
	{
		ft_lstclear(head, free); // todo: pass custom function to free?
		free(head);
		return (1);
	}
	ft_lstadd_front(head, elem);
	return (0);
}

char	*chop_word_by_space(char **line)
{
	char	*word;

	skip_spaces(line);
	word = *line;
	while (!ft_isspace(**line))
		(*line)++;
	(*line) = 0;
	(*line)++;
	return (word);
}

int	add_ambient(char *line, t_list **head)
{
	t_ambient	*elem;
	char		*word;

	if (check_exist('A', head))
		return (1);
	elem = malloc(sizeof(t_ambient));
	if (!elem)
		return (1);
	word = chop_word_by_space(&line);
	//todo: replace with custom atof && error checking
	elem->brightness = atof(word);
	printf("%f\n", elem->brightness);
	word = chop_word_by_space(&line);
	elem->colour.x = ft_atoi(word);
	printf("%f\n", elem->brightness);
	word = chop_word_by_space(&line);
	elem->colour.y = ft_atoi(word);
	printf("%f\n", elem->brightness);
	word = chop_word_by_space(&line);
	elem->colour.z = ft_atoi(word);
	printf("%f\n", elem->brightness);

	skip_spaces(&line);
	if (*line) // still some content at the end of line
		return (1);
	if (new_lst(head))
		return (1);
	(*head)->content = elem;
	return (0);

}

int	parse_line(char *line, t_list **head)
{
	int	ret;

	ret = 1;
	if (line[0] == 'A' && ft_isspace(line[1]))
		ret = add_ambient(line + 1, head);
	return (ret);
}

int parser(int argc, char **argv)
{
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	char	*line;
	t_list **head;

	if (argc < 2)
		return (1);
	head = malloc(sizeof(t_list *));
	if (!head)
		return (1);
	int fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line)
		{
			ft_printf(2, "%d %s\n", *line, line);
			if (parse_line(line, head))
			{
				// todo: maybe custom error message depending on the error
				ft_printf(2, "Error\nCould not parse the file");
				return (1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}