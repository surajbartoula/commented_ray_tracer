/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_box_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:06:01 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 13:32:27 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	check_sphere_box_collision(t_shape *box, t_shape *sphere,
	t_vector *point_on_box, t_vector *box_to_sphere)
{
	*point_on_box = closest_point_on_box(&sphere->origin, box);
	sub_vector(box_to_sphere, point_on_box, &sphere->origin);
	return (dot_product(box_to_sphere, box_to_sphere)
		<= sphere->props.radius_squared);
}

bool	sphere_box_collision(t_shape *box, t_shape *sphere, bool box_sphere,
	bool resolve)
{
	t_vector	point_on_box;
	t_vector	resolution;
	double		distance;
	t_vector	box_to_sphere;

	if (check_sphere_box_collision(box, sphere, &point_on_box, &box_to_sphere))
	{
		if (resolve)
		{
			sub_vector(&resolution, &sphere->origin, &point_on_box);
			if (vector_magnitude(&resolution) < 0.0001)
				return (true);
			normalize_vector(&resolution);
			distance = vector_distance(&point_on_box, &sphere->origin);
			scale_vector(&resolution, &resolution, sphere->props.radius
				- distance);
			if (box_sphere)
				add_vector(&sphere->origin, &sphere->origin, &resolution);
			else
				sub_vector(&box->origin, &box->origin, &resolution);
		}
		return (true);
	}
	return (false);
}
