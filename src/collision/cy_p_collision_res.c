/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_p_collision_res.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:39:57 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 02:21:07 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static bool	handle_parallel_case(t_cy_collision_data *cy_data,
	t_shape *cylinder, t_shape *plane)
{
	double	normal_dot_product;
	double	dist;

	normal_dot_product = fabs(dot_product(&plane->orientation,
				&cy_data->cylinder_normal));
	if (fabs(normal_dot_product - 1) >= 0.00001)
		return (false);
	cy_data->resolution = plane->orientation;
	dist = fabs(dot_product(&cy_data->cap_center, &plane->orientation));
	scale_vector(&cy_data->resolution, &cy_data->resolution, dist + 0.001);
	add_vector(&cylinder->origin, &cylinder->origin, &cy_data->resolution);
	return (true);
}

static void	select_nearest_cap(t_cy_collision_data *cy_data, t_shape *plane)
{
	t_vector	cap_to_plane;
	double		d1;
	double		d2;

	sub_vector(&cap_to_plane, &cy_data->top_cap_center, &plane->origin);
	d1 = fabs(dot_product(&cap_to_plane, &plane->orientation));
	sub_vector(&cap_to_plane, &cy_data->bottom_cap_center, &plane->origin);
	d2 = fabs(dot_product(&cap_to_plane, &plane->orientation));
	if (d1 < d2)
		cy_data->cap_center = cy_data->top_cap_center;
	else
		cy_data->cap_center = cy_data->bottom_cap_center;
}

static void	compute_cylinder_cap_centers(t_cy_collision_data *cy_data,
	t_shape *cylinder)
{
	scale_vector(&cy_data->top_cap_center, &cy_data->cylinder_normal,
		-cylinder->props.height / 2);
	add_vector(&cy_data->bottom_cap_center, &cy_data->bottom_cap_center,
		&cylinder->origin);
	scale_vector(&cy_data->bottom_cap_center, &cy_data->cylinder_normal,
		-cylinder->props.height / 2);
	add_vector(&cy_data->bottom_cap_center, &cy_data->bottom_cap_center,
		&cylinder->origin);
}

static bool	get_cylinder_normal(t_vector *cylinder_normal, t_shape *cylinder)
{
	t_vector	up_vector;

	ft_bzero(&up_vector, sizeof(t_vector));
	up_vector.y = 1;
	mat4_multiply(cylinder_normal, &cylinder->transf, &up_vector);
	if (vector_magnitude(cylinder_normal) < 0.001)
		return (false);
	normalize_vector(cylinder_normal);
	return (true);
}

void	cylinder_plane_collision_resolution(t_shape *cylinder, t_shape *plane)
{
	t_cy_collision_data	cy_data;

	if (!get_cylinder_normal(&cy_data.cylinder_normal, cylinder))
		return ;
	compute_cylinder_cap_centers(&cy_data, cylinder);
	select_nearest_cap(&cy_data, plane);
	if (handle_parallel_case(&cy_data, cylinder, plane))
		return ;
	handle_secondary_plane_case(&cy_data, cylinder, plane);
}
