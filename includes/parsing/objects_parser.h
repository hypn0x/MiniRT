/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:06:54 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 00:06:56 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by segransm on 1/26/22.
//

#ifndef OBJECTS_PARSER_H
# define OBJECTS_PARSER_H

# include <libft.h>

int	add_sphere(char *line, t_list **head);

int	add_plane(char *line, t_list **head);

int	add_cylinder(char *line, t_list **head);

#endif //OBJECTS_PARSER_H
