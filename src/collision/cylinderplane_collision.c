/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinderplane_collision.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:36:55 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/04 23:01:25 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	get_cylinder_normal(t_shape *cylinder, t_vector *cylinder_normal)
{
	t_vector	up_vector;

	ft_bzero(&up_vector, sizeof(t_vector));
	up_vector.y = 1;
	mat_vec_mult(cylinder_normal, &cylinder->transf, &up_vector);
	if (vector_magnitude(cylinder_normal) < 0.001)
	{
		return (false);
	}
	normalize_vector(cylinder_normal);
	return (true);
}

bool	cylinder_plane_collision(t_shape *cylinder, t_shape *plane)
{
	t_vector	cylinder_normal;
	t_vector	cylinder_to_plane;
	double		cylinder_to_plane_proj;
	double		normal_dot_product;

	if (!get_cylinder_normal(cylinder, &cylinder_normal))
	{
		return (false);
	}
	sub_vector(&cylinder_to_plane, &cylinder->origin, &plane->origin);
	cylinder_to_plane_proj = fabs(dot_product(&plane->orientation,
				&cylinder_to_plane));
	normal_dot_product = fabs(dot_product(&plane->orientation,
				&cylinder_normal));
	if (fabs(normal_dot_product - 1) < 0.001)
	{
		return (cylinder_to_plane_proj <= cylinder->props.height / 2);
	}
	return (cylinder_to_plane_proj < cylinder->props.radius
		* sqrt(1 - normal_dot_product * normal_dot_product)
		+ (cylinder->props.height / 2) * normal_dot_product);
}
