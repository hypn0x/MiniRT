/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:48:58 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/31 15:49:01 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifndef M_PI
#  define M_PI		3.14159265358979323846	/* pi */
# endif
# ifndef M_PI_2
#  define M_PI_2		1.57079632679489661923	/* pi/2 */
# endif
# define IMG_W 1080
# define ASPECT_RATIO (16.0 / 9.0)
# define IMG_H (int)(IMG_W / ASPECT_RATIO)

#endif //CONSTANTS_H
