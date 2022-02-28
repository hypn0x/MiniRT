/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:40:12 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/28 21:40:14 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Hajar Sabir on 2/8/22.
//

#ifndef COLORS_H
# define COLORS_H

# include <types.h>

t_list		*get_hit_elem(t_ray r, t_list **head, float *distance);

int			rgb_to_int(t_colour c);

t_colour	get_pixel_colour(t_data img, t_object obj, t_ray r);

t_colour	get_elem_colour(t_list *hit_elem, t_ray r, t_data img,
				float distance);

#endif //COLORS_H
