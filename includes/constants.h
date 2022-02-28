/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:48:58 by msegrans          #+#    #+#             */
/*   Updated: 2022/02/28 16:59:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifndef M_PI
#  define M_PI		3.14159265358979323846f	/* pi */
# endif
# ifndef M_PI_2
#  define M_PI_2		1.57079632679489661923f	/* pi/2 */
# endif
# define IMG_W 1920
# define ASPECT_RATIO (16.0f / 9.0f)
# define IMG_H (int)(IMG_W / ASPECT_RATIO)
# ifndef SUPERSAMPLING
#  define SUPERSAMPLING 1
# endif
#endif //CONSTANTS_H
