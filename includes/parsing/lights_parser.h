/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:38:31 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/18 14:02:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by segransm on 1/26/22.
//

#ifndef LIGHTS_PARSER_H
# define LIGHTS_PARSER_H

# include <libft.h>

int	add_ambient(char *line, t_ambient *A);

int	add_camera(char *line, t_camera *C);

int	add_light(char *line, t_list **L);

#endif //LIGHTS_PARSER_H
