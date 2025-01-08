/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_box_overlap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:02:15 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/07 12:12:07 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	 initialize_box_axes(t_box_axes *ba)
{
	ba->res_distance = INFINITY;
	ba->res_axis = (t_vector){0, 0, 0, 0};
}

void	extract_unit_vectors(t_shape *shape, t_vector *unit_vectors)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		unit_vectors[i].x = shape->added_rots[0][i];
		unit_vectors[i].y = shape->added_rots[1][i];
		unit_vectors[i].z = shape->added_rots[2][i];
		unit_vectors[i].w = 0;
		normalize_vector(&unit_vectors[i]);
		i++;
	}
}

void	calculate_rotation_matrices(t_box_axes *ba)
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ba->rot[i][j] = dot_product(&ba->b1_u[i], &ba->b2_u[j]);
			ba->abs_rot[i][j] = fabs(ba->rot[i][j]) + EPSILON;
			j++;
		}
		i++;
	}
}

void	compute_center_distance(t_box_axes *ba, t_shape *b1, t_shape *b2)
{
	int		i;

	i = 0;
	sub_vector(&ba->center_distance, &b2->origin, &b1->origin);
	while (i < 3)
	{
		ba->t[i] = dot_product(&ba->center_distance, &ba->b1_u[i]);
		i++;
	}
}

bool	test_axis_overlap(t_box_axes *ba, t_shape *b1, t_shape *b2, int axis)
{
	ba->ra = b1->props.scale.x * fabs(ba->abs_rot[0][axis])
		+ b1->props.scale.y * fabs(ba->abs_rot[1][axis])
		+ b1->props.scale.z * fabs(ba->abs_rot[2][axis]);
	ba->rb = b2->props.scale.x * fabs(ba->abs_rot[axis][0])
		+ b2->props.scale.x * fabs(ba->abs_rot[axis][0])
		+ b1->props.scale.y * fabs(ba->abs_rot[axis][1])
		+ b1->props.scale.z * fabs(ba->abs_rot[axis][2]);
	if (fabs(ba->t[axis]) > ba->ra + ba->rb)
		return (false);
	if ((ba->ra + ba->rb - fabs(ba->t[axis])) < ba->res_distance)
	{
		ba->res_distance = ba->ra + ba->rb - fabs(ba->t[axis]);
		ba->res_axis = ba->b1_u[axis];
		if (ba->t[axis] < 0)
			negate_vector(&ba->res_axis, &ba->res_axis);
	}
	return (true);
}
