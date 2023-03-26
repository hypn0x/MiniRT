/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:32:52 by                   #+#    #+#             */
/*   Updated: 2022/02/27 12:31:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hit_objs.h>
#include <op_vec.h>
#include <math.h>

float hit_cylinder(t_cylinder *cylinder, t_ray ray)
{
	// Coefficients of the quadratic equation
	float a_coefficient;
	float b_coefficient;
	float c_coefficient;
	// Discriminant
	float disc;
	// solutions of the quadratic equation
	float t1;
	float t2;
	// distance from the origin of the ray to the intersection point
	float m1;
	float m2;

	// used to solve m and t
	t_vec3 closest_ray_intersection = min_vec(ray.origin, cylinder->coordinates);
	// used to find the a_coefficient coefficient -> a = D|D - (D|V)^2
	float VD = dot(ray.direction, cylinder->orientation);
	float COD = dot(closest_ray_intersection, cylinder->orientation);

	// a = D|D - (D|V)^2
	a_coefficient = dot(ray.direction, ray.direction) - VD * VD;
	// b = 2 * (D|X - (D|V)*(X|V))
	b_coefficient = 2 * (dot(ray.direction, closest_ray_intersection) - VD * COD);
	// c = X|X - (X|V)^2 - r^2
	c_coefficient = dot(closest_ray_intersection, closest_ray_intersection) - COD * COD - cylinder->diameter * cylinder->diameter / 4.0;

	// b^2 - 4ac
	disc = b_coefficient * b_coefficient - 4 * a_coefficient * c_coefficient;
	if (disc < 0)
		return -1;

	// Quadratic equation -> t = (-b +- sqrt(b^2 - 4ac)) / 2a
	t1 = (-b_coefficient + sqrtf(disc)) / (2 * a_coefficient);
	t2 = (-b_coefficient - sqrtf(disc)) / (2 * a_coefficient);

	// m = (D|V)t + (X|V) : It is usefully because we don't want to intersect with the infinite cylinder
	m1 = dot(ray.direction, cylinder->orientation) * t1 + dot(closest_ray_intersection, cylinder->orientation);
	m2 = dot(ray.direction, cylinder->orientation) * t2 + dot(closest_ray_intersection, cylinder->orientation);

	// The intersection point must be between 0 and the height of the cylinder
	if (m1 < 0 || m1 > cylinder->height)
		t1 = -1;
	if (m2 < 0 || m2 > cylinder->height)
		t2 = -1;

	// Return the smallest positive value
	if (t1 > 0 && t2 > 0)
		return (t1 < t2 ? t1 : t2);
	else if (t1 > 0)
		return t1;
	else if (t2 > 0)
		return t2;
	else
		return -1;
}
