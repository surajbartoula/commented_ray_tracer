/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:50:13 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/04 11:25:07 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	vec_magnitude(const t_vector *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y \
			+ vec->z * vec->z));
}

bool	is_shadow(t_scene *scene, int light_idx, t_vector *itx_point,
			double *angle)
{
	double			distance;
	int				i;
	t_ray			ray;
	t_intersections	arr;
	t_intersection	*itx;

	sub_vector(&ray.dir, &scene->lights[light_idx].position, itx_point);
	distance = vec_magnitude(&ray.dir);
	scale_vector(&ray.dir, &ray.dir, 1 / distance);
	ray.origin = *itx_point;
	if (check_spotlight(scene, light_idx, &ray, angle) == true)
		return (true);
	i = -1;
	arr.count = 0;
	while (++i < scene->count.shapes)
		intersect(&scene->shapes[i], &ray, &arr);
	itx = hit(&arr);
	if (itx && itx->time < distance)
		return (true);
	return (false);
}

t_color	coloring(int hex_color)
{
	t_color	color;

	color.a = 0;
	color.r = ((unsigned char *)&hex_color)[2] / 255.0f;
	color.g = ((unsigned char *)&hex_color)[1] / 255.0f;
	color.b = ((unsigned char *)&hex_color)[0] / 255.0f;
	return (color);
}
