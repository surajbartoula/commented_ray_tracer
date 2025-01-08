/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_resolution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:40:34 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/30 12:41:45 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	sphere_sphere_collision_resolution(t_shape *sphere1, t_shape *sphere2)
{
	t_vector	dir;
	double		dist;

	sub_vector(&dir, &sphere1->origin, &sphere2->origin);
	dist = vector_magnitude(&dir);
	if (dist < 0.001)
		return ;
	normalize_vector(&dir);
	scale_vector(&dir, &dir, dist - (sphere1->props.radius
			+ sphere2->props.radius) - 0.001);
	add_vector(&sphere2->origin, &sphere2->origin, &dir);
}

void	resolve_sphere_sphere(t_shape *shape1, t_shape *shape2,
	t_shape *transformed_shape)
{
	if (shape2 == transformed_shape)
		sphere_sphere_collision_resolution(shape2, shape1);
	else
		sphere_sphere_collision_resolution(shape1, shape2);
}

void	box_box_collision_resolution(t_shape *shape1, t_shape *shape2,
	t_shape *transformed_shape)
{
	if (shape2 == transformed_shape)
		box_box_collision(shape2, shape1, true);
	else
		box_box_collision(shape1, shape2, true);
}
