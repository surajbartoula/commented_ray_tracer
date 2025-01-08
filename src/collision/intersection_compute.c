/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_compute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:23:08 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 18:07:47 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	ray_position(t_vector *pos, const t_ray *ray, double time)
{
	pos->x = ray->dir.x * time + ray->origin.x;
	pos->y = ray->dir.y * time + ray->origin.y;
	pos->z = ray->dir.z * time + ray->origin.z;
	pos->w = 1;
}

void	transform_ray(t_ray *transformed_ray, const t_ray *ray,
	const t_shape *shape)
{
	mat_vec_mult(&transformed_ray->origin, &shape->inv_transf,
		&ray->origin);
	mat_vec_mult(&transformed_ray->dir, &shape->inv_transf,
		&ray->dir);
}

void	prepare_computations(t_intersection *intersection,
			t_ray *ray)
{
	ray_position(&intersection->point, ray, intersection->time);
	intersection->normal = normal_at(intersection->shape, &intersection->point);
	negate_vector(&intersection->eye, &ray->dir);
	intersection->eye.w = 0;
	intersection->inside = false;
	if (dot_product(&intersection->normal, &intersection->eye) < 0)
	{
		intersection->inside = true;
		negate_vector(&intersection->normal, &intersection->normal);
	}
	scale_vector(&intersection->over_point, &intersection->normal, EPSILON);
	add_vector(&intersection->over_point, &intersection->point,
		&intersection->over_point);
	reflect_vector(&intersection->reflect_vec, &ray->dir,
		&intersection->normal);
}

t_intersection	*hit(t_intersections *xs)
{
	double	min_time;
	int		i;
	int		idx;

	i = 0;
	idx = 0;
	min_time = INFINITY;
	while (i < xs->count)
	{
		if (xs->arr[i].time >= 0 && xs->arr[i].time < min_time)
		{
			min_time = xs->arr[i].time;
			idx = i;
		}
		i++;
	}
	if (min_time == INFINITY)
		return (NULL);
	return (&xs->arr[idx]);
}
