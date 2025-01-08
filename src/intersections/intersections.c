/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:39:29 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/08 21:49:26 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	intersect_sphere_fast(const t_ray *ray, t_intersections *xs,
	t_shape *sphere)
{
	t_vector	oc; //origin to sphere center
	double		b; //The projection of oc onto the ray's direction vector d
	double		c; //oc.oc - r(squared) distance from the ray origin to the sphere's surface squared.
	double		h;

	//
	sub_vector(&oc, &ray->origin, &sphere->origin);
	b = dot_product(&oc, &ray->dir);
	c = dot_product(&oc, &oc) - sphere->props.radius_squared;
	//calculating the discriminant h = b₂ - c
	h = b * b - c;
	if (h < 0.0)
		return (false);
	//calculate intersection point
	h = sqrt(h);
	//if h > 0 then since the formula is -sqr(b) +- 4ac so there will be 2 points.
	xs->arr[xs->count].time = -b - h;
	xs->arr[xs->count].shape = sphere;
	xs->arr[xs->count + 1].time = -b + h;
	xs->arr[xs->count + 1].shape = sphere;
	xs->count += 2;
	return (true);
}

//calculates the intersection times (t_min and t_max) for a ray along a specific axis of a cube.
void	check_cube_axis(double *t_min, double *t_max, double origin,
		double direction)
{
	double	tmin_numerator;
	double	tmax_numerator;

//represent the distances from the ray's origin to the cube's planes along the axis.
//Cube boundries are assumed to be [-1, 1] on each axis.
	tmin_numerator = (-1 - origin);
	tmax_numerator = 1 - origin;
	//Not parallel to the axis
	if (fabs(direction) >= 0.000001)
	{
		*t_min = tmin_numerator / direction;
		*t_max = tmax_numerator / direction;
	}
	//handle parallel rays
	else
	{
		*t_min = tmin_numerator * INFINITY;
		*t_max = tmax_numerator * INFINITY;
	}
	if (*t_min > *t_max)
		ft_swapd(t_min, t_max);
}

////records the times of intersection t(min) and t(max)
bool	intersect_cube(t_shape *shape, t_ray *ray, t_intersections *xs)
{
	t_vector	tmin_vec;
	//tmin_vec.axis: The time when the ray enters the cube's slab along the given axis.
	t_vector	tmax_vec;
	//tmax_vec.axis: The time when the ray exits the cube's slab along the given axis.
	double		tmin;
	double		tmax;

	check_cube_axis(&tmin_vec.x, &tmax_vec.x, ray->origin.x, ray->dir.x);
	check_cube_axis(&tmin_vec.y, &tmax_vec.y, ray->origin.y, ray->dir.y);
	check_cube_axis(&tmin_vec.z, &tmax_vec.z, ray->origin.z, ray->dir.z);
	tmin = max_with_three(tmin_vec.x, tmin_vec.y, tmin_vec.z);
	tmax = min_with_three(tmax_vec.x, tmax_vec.y, tmax_vec.z);
	if (tmin > tmax)
		return (false);
	xs->arr[xs->count].time = tmin;
	xs->arr[xs->count].shape = shape;
	xs->arr[xs->count + 1].time = tmax;
	xs->arr[xs->count + 1].shape = shape;
	xs->count += 2;
	return (true);
}

bool	intersect_plane_fast(const t_ray *ray, t_shape *plane,
		t_intersections *xs)
{
	double	denom;

	//V.N calculation. t = -(O.N - D)/V.N. if V.N is less than 0 then the t will be infinite means no intersection.
	denom = dot_product(&ray->dir, &plane->orientation);
	if (fabs(denom) < 0.00001)
		return (false);
	xs->arr[xs->count].time = -(dot_product(&ray->origin, &plane->orientation) \
		- plane->props.distance_from_origin) / denom;
	xs->arr[xs->count].shape = plane;
	xs->count++;
	return (true);
}
