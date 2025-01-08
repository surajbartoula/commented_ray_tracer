/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:39:29 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/28 11:53:33 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	intersect_sphere_fast(const t_ray *ray, t_intersections *xs,
	t_shape *sphere)
{
	t_vector	oc;
	double		b;
	double		c;
	double		h;

	sub_vector(&oc, &ray->origin, &sphere->origin);
	b = dot_product(&oc, &ray->dir);
	c = dot_product(&oc, &oc) - sphere->props.radius_squared;
	h = b * b - c;
	if (h < 0.0)
		return (false);
	h = sqrt(h);
	xs->arr[xs->count].time = -b - h;
	xs->arr[xs->count].shape = sphere;
	xs->arr[xs->count + 1].time = -b + h;
	xs->arr[xs->count + 1].shape = sphere;
	xs->count += 2;
	return (true);
}

void	check_cube_axis(double *t_min, double *t_max, double origin,
		double direction)
{
	double	tmin_numerator;
	double	tmax_numerator;

	tmin_numerator = (-1 - origin);
	tmax_numerator = 1 - origin;
	if (fabs(direction) >= 0.000001)
	{
		*t_min = tmin_numerator / direction;
		*t_max = tmax_numerator / direction;
	}
	else
	{
		*t_min = tmin_numerator * INFINITY;
		*t_max = tmax_numerator * INFINITY;
	}
	if (*t_min > *t_max)
		ft_swapd(t_min, t_max);
}

bool	intersect_cube(t_shape *shape, t_ray *ray, t_intersections *xs)
{
	t_vector	tmin_vec;
	t_vector	tmax_vec;
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

	denom = dot_product(&ray->dir, &plane->orientation);
	if (fabs(denom) < 0.00001)
		return (false);
	xs->arr[xs->count].time = -(dot_product(&ray->origin, &plane->orientation) \
		- plane->props.distance_from_origin) / denom;
	xs->arr[xs->count].shape = plane;
	xs->count++;
	return (true);
}
