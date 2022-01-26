//
// Created by segransm on 1/26/22.
//

#include <libft.h>
#include <types.h>

void	skip_spaces(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

int	check_exist(char type, t_list **head)
{
	t_list	*elem;

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

char	*chop_word(char **line, int (fn)(int))
{
	char	*word;

	skip_spaces(line);
	word = *line;
	while (**line && !fn(**line))
		(*line)++;
	if (**line)
	{
		**line = 0;
		(*line)++;
	}
	return (word);
}

int	is_comma(int c)
{
	return (c == ',');
}

int	parse_vec3(char **line, t_vec3 *elem)
{
	char	*word;

	word = chop_word(line, is_comma);
	elem->x = atof(word);
	word = chop_word(line, is_comma);
	elem->y = atof(word);
	word = chop_word(line, ft_isspace);
	elem->z = atof(word);
	return (0);
}
