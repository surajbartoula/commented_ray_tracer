/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:28:03 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:56:16 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vector	cylinder_normal(const t_shape *shape, const t_vector *itx_point)
{
	double		distance;
	t_vector	normal;
	t_vector	point;
	t_vector	world_normal;

	mat_vec_mult(&point, &shape->inv_transf, itx_point);
	point.w = 0;
	distance = point.x * point.x + point.z * point.z;
	ft_bzero(&normal, sizeof(t_vector));
	if (distance < 1 && (point.y >= (shape->props.height / 2) - EPSILON))
		normal.y = 1;
	else if (distance < 1 && (point.y <= -(shape->props.height / 2) + EPSILON))
		normal.y = -1;
	else
	{
		normal.x = point.x;
		normal.z = point.z;
		normalize_vector(&normal);
	}
	if (shape->normal_tex != NULL)
		return (normal_map(&normal, shape, itx_point));
	mat_vec_mult(&world_normal, &shape->norm_transf, &normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}

t_vector	cone_normal(const t_shape *shape, const t_vector *itx_point)
{
	double		distance;
	t_vector	normal;
	t_vector	point;
	t_vector	world_normal;

	mat_vec_mult(&point, &shape->inv_transf, itx_point);
	distance = point.x * point.x + point.z * point.z;
	ft_bzero(&normal, sizeof(t_vector));
	if (distance < fabs(point.y) * fabs(point.y) && (point.y >= 0.5 - EPSILON))
		normal.y = 1;
	else if (distance < fabs(point.y) * fabs(point.y) && (point.y <= EPSILON))
		normal.y = -1;
	else
	{
		normal.y = sqrt(distance);
		if (point.y > 0)
			normal.y *= -1;
		normal = (t_vector){point.x, normal.y, point.z, 0};
		normalize_vector(&normal);
	}
	if (shape->normal_tex != NULL)
		return (normal_map(&normal, shape, itx_point));
	mat_vec_mult(&world_normal, &shape->norm_transf, &normal);
	normalize_vector(&world_normal);
	return (world_normal);
}

t_vector	plane_normal(const t_shape *shape, const t_vector *itx_point)
{
	t_vector	object_normal;
	t_vector	world_normal;

	object_normal.x = 0;
	object_normal.y = 1;
	object_normal.z = 0;
	object_normal.w = 0;
	if (shape->normal_tex != NULL)
		return (normal_map(&object_normal, shape, itx_point));
	mat_vec_mult(&world_normal, &shape->norm_transf, &object_normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}

t_vector	cube_normal(const t_shape *shape, const t_vector *itx_point)
{
	double		maxc;
	t_vector	normal;

	mat_vec_mult(&normal, &shape->inv_transf, itx_point);
	normal.w = 0;
	maxc = max_with_three(fabs(normal.x), fabs(normal.y), fabs(normal.z));
	if (maxc == fabs(normal.x))
	{
		normal.y = 0;
		normal.z = 0;
	}
	else if (maxc == fabs(normal.y))
	{
		normal.x = 0;
		normal.z = 0;
	}
	else if (maxc == fabs(normal.z))
	{
		normal.x = 0;
		normal.y = 0;
	}
	normalize_vector(&normal);
	return (normal);
}

t_vector	sphere_normal(t_vector *normal, const t_shape *shape,
				const t_vector *itx_point)
{
	t_vector	world_normal;

	mat_vec_mult(normal, &shape->inv_transf, itx_point);
	normalize_vector(normal);
	normal->w = 0;
	if (shape->normal_tex != NULL)
		return (normal_map(normal, shape, itx_point));
	mat_vec_mult(&world_normal, &shape->norm_transf, normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}
