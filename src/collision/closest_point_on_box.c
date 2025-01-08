/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_point_on_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:19:59 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 01:36:58 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vector	get_box_axis(const t_shape *box, int index)
{
	t_vector	axis;

	axis.x = box->added_rots[0][index];
	axis.y = box->added_rots[1][index];
	axis.z = box->added_rots[2][index];
	axis.w = 0;
	normalize_vector(&axis);
	return (axis);
}

double	clamp_distance(double distance, double scale)
{
	if (distance > scale)
		return (scale);
	if (distance < -scale)
		return (-scale);
	return (distance);
}

void	project_point_to_axis(t_vector *closest,
	const t_vector *point_to_center, t_vector *axis, double scale)
{
	t_vector	step;
	double		distance;

	distance = dot_product(point_to_center, axis);
	distance = clamp_distance(distance, scale);
	scale_vector(&step, axis, distance);
	add_vector(closest, closest, &step);
}

t_vector	closest_point_on_box(const t_vector *point, const t_shape *box)
{
	t_vector	point_to_center;
	t_vector	closest;
	t_vector	box_u;
	t_vector	box_v;
	t_vector	box_w;

	ft_bzero(&closest, sizeof(t_vector));
	sub_vector(&point_to_center, point, &box->origin);
	closest = box->origin;
	box_u = get_box_axis(box, 0);
	box_v = get_box_axis(box, 1);
	box_w = get_box_axis(box, 2);
	project_point_to_axis(&closest, &point_to_center,
		&box_u, box->props.scale.x);
	project_point_to_axis(&closest, &point_to_center,
		&box_v, box->props.scale.y);
	project_point_to_axis(&closest, &point_to_center, &box_w,
		box->props.scale.z);
	return (closest);
}
