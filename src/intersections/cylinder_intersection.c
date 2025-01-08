/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:42:41 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/08 21:50:59 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static bool	within_cylinder_radius(const t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + ray->dir.x * t;
	z = ray->origin.z + ray->dir.z * t;
	if ((x * x + z * z) <= 1)
		return (true);
	return (false);
}

static bool	check_cylinder_caps(const t_ray *ray, t_shape *shape,
		t_intersections *xs)
{
	bool	intersected;
	double	t;

	intersected = false;
	if (fabs(ray->dir.y) > EPSILON)
	{
		t = (-(shape->props.height / 2) - ray->origin.y) / ray->dir.y;
		if (within_cylinder_radius(ray, t))
		{
			xs->arr[xs->count].time = t;
			xs->arr[xs->count].shape = shape;
			xs->count++;
			intersected = true;
		}
		t = ((shape->props.height / 2) - ray->origin.y) / ray->dir.y;
		if (within_cylinder_radius(ray, t))
		{
			xs->arr[xs->count].time = t;
			xs->arr[xs->count].shape = shape;
			xs->count++;
			intersected = true;
		}
	}
	return (intersected);
}

//checks whether a given ray intersects with a cylindrical shape and records the intersection
//times if they occur within the bounds of the cylinder's height.
static bool	add_cylinder_intersections(t_shape *shape, const t_ray *ray,
		t_intersections *xs, double *ts)
{
	double	y0;
	double	y1;
	bool	intersected;

	intersected = false;
	if (ts[0] > ts[1])
		ft_swapd(&ts[0], &ts[1]);
	//Calculate Intersection Y-Coordinates:
	y0 = ray->origin.y + ts[0] * ray->dir.y;
	//Check Cylinder Height Bounds:
	if (y0 > (-shape->props.height / 2) && y0 < (shape->props.height / 2))
	{
		xs->arr[xs->count].time = ts[0];
		xs->arr[xs->count].shape = shape;
		xs->count++;
		intersected = true;
	}
	y1 = ray->origin.y + ts[1] * ray->dir.y;
	//Record Valid Intersections:
	if (y1 > (-shape->props.height / 2) && y1 < (shape->props.height / 2))
	{
		xs->arr[xs->count].time = ts[1];
		xs->arr[xs->count].shape = shape;
		xs->count++;
		intersected = true;
	}
	return (intersected);
}

bool	intersect_cylinder(const t_ray *ray, t_shape *shape,
	t_intersections *xs)
{
	bool	intersected;
	double	a;
	double	b;
	double	ts[2];
	double	discriminant;

	//check the intersection with cap
	intersected = check_cylinder_caps(ray, shape, xs);
	//If a is close to zero (i.e., the ray is moving only along the y-axis),
	//it means the ray is parallel to the cylinder, and there’s no intersection. 
	//In that case, the function returns early.
	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	if (fabs(a) < 0.0001)
		return (intersected);
	b = 2 * ray->dir.x * ray->origin.x + 2 * ray->dir.z * ray->origin.z;
	discriminant = b * b - 4 * a * \
		(ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1);
	if (discriminant < 0)
		return (intersected);
	a *= 2;
	b *= -1;
	discriminant = sqrt(discriminant);
	ts[0] = (b - discriminant) / (a);
	ts[1] = (b + discriminant) / (a);
	if (add_cylinder_intersections(shape, ray, xs, ts))
		intersected = true;
	return (intersected);
}
