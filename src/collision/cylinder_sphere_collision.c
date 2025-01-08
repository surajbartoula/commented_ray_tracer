/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_sphere_collision.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:37:35 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:59:33 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	calculate_cylinder_normal(t_cy_collision_data *data, t_shape *cylinder)
{
	t_vector	up_vector;

	up_vector.x = 0;
	up_vector.y = 1;
	up_vector.z = 0;
	up_vector.w = 0;
	mat4_multiply(&data->cylinder_normal, &cylinder->transf, &up_vector);
	if (fabs(vec_magnitude(&data->cylinder_normal)) < 0.001)
		return (false);
	normalize_vector(&data->cylinder_normal);
	return (true);
}

void	calculate_caps(t_cy_collision_data *data, t_shape *cylinder)
{
	scale_vector(&data->top_cap_center, &data->cylinder_normal,
		cylinder->props.height / 2);
	add_vector(&data->top_cap_center, &data->top_cap_center, &cylinder->origin);
	scale_vector(&data->bottom_cap_center, &data->cylinder_normal,
		-cylinder->props.height / 2);
	add_vector(&data->bottom_cap_center, &data->bottom_cap_center,
		&cylinder->origin);
}

bool	check_caps_collision(t_cy_collision_data *col_data,
	t_cy_sp_data *sp_data, t_collision_inputs *inputs)
{
	sub_vector(&sp_data->cap_to_sphere, &col_data->cap_center,
		&inputs->sphere->origin);
	sp_data->dist = vec_magnitude(&sp_data->cap_to_sphere);
	sp_data->v_cap_distance = fabs(dot_product(&sp_data->cap_to_sphere,
				&col_data->cylinder_normal));
	if ((sp_data->dist * sp_data->dist - sp_data->v_cap_distance
			* sp_data->v_cap_distance) < 0)
		return (false);
	sp_data->h_cap_distance = sqrt(sp_data->dist * sp_data->dist
			- sp_data->v_cap_distance * sp_data->v_cap_distance);
	if (sp_data->h_cap_distance < inputs->cylinder->props.radius
		&& sp_data->v_cap_distance < inputs->sphere->props.radius)
	{
		col_data->resolution = col_data->cylinder_normal;
		if (inputs->resolve)
		{
			scale_vector(&col_data->resolution, &col_data->resolution,
				inputs->sphere->props.radius - sp_data->v_cap_distance - 0.001);
			add_vector(&inputs->sphere->origin, &inputs->sphere->origin,
				&col_data->resolution);
		}
		return (true);
	}
	return (false);
}

bool	check_side_collision(t_cy_collision_data *col_data,
	t_cy_sp_data *sp_data, t_collision_inputs *inputs, double radius_sum) {
	scale_vector(&sp_data->center_delta, &col_data->cylinder_normal,
		-sp_data->v_dist);
	add_vector(&sp_data->center_adjusted, &inputs->cylinder->origin,
		&sp_data->center_delta);
	sp_data->dist = vector_distance(&sp_data->center_adjusted,
			&inputs->sphere->origin);
	if (sp_data->dist < radius_sum)
	{
		sub_vector(&col_data->resolution, &sp_data->center_adjusted,
			&inputs->sphere->origin);
		negate_vector(&col_data->resolution, &col_data->resolution);
		if (vec_magnitude(&col_data->resolution) < 0.001)
			return (false);
		normalize_vector(&col_data->resolution);
		if (inputs->resolve)
		{
			scale_vector(&col_data->resolution, &col_data->resolution,
				radius_sum - sp_data->dist - 0.001);
			add_vector(&inputs->sphere->origin, &inputs->sphere->origin,
				&col_data->resolution);
		}
		return (true);
	}
	return (false);
}

bool	cylinder_sphere_collision(t_shape *cylinder, t_shape *sphere,
		bool resolve)
{
	t_cy_collision_data	col_data;
	t_cy_sp_data		sp_data;
	t_collision_inputs	inputs;
	double				radius_sum;

	inputs.cylinder = cylinder;
	inputs.sphere = sphere;
	inputs.resolve = resolve;
	radius_sum = cylinder->props.radius + sphere->props.radius;
	if (!calculate_cylinder_normal(&col_data, cylinder))
		return (false);
	calculate_caps(&col_data, cylinder);
	col_data.cap_center = col_data.top_cap_center;
	if (check_caps_collision(&col_data, &sp_data, &inputs))
		return (true);
	col_data.cap_center = col_data.bottom_cap_center;
	if (check_caps_collision(&col_data, &sp_data, &inputs))
		return (true);
	sub_vector(&sp_data.cylinder_to_sphere, &cylinder->origin, &sphere->origin);
	sp_data.v_dist = dot_product(&sp_data.cylinder_to_sphere,
			&col_data.cylinder_normal);
	if (check_side_collision(&col_data, &sp_data, &inputs, radius_sum))
		return (true);
	return (false);
}
