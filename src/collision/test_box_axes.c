/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_box_axes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:31:52 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/07 12:43:34 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void	resolve_resolution(t_vector *resolution, t_box_axes *ba)
{
	if (resolution)
	{
		*resolution = ba->res_axis;
		normalize_vector(resolution);
		scale_vector(resolution, resolution, ba->res_distance + 0.0001);
	}
}

bool	test_box_axes(t_shape *b1, t_shape *b2, t_vector *resolution)
{
	t_box_axes	ba;
	int			i;

	initialize_box_axes(&ba);
	extract_unit_vectors(b1, ba.b1_u);
	extract_unit_vectors(b2, ba.b2_u);
	calculate_rotation_matrices(&ba);
	compute_center_distance(&ba, b1, b2);
	i = 0;
	while (i < 3)
	{
		if (!test_axis_overlap(&ba, b1, b2, i))
			return (false);
		i++;
	}
	resolve_resolution(resolution, &ba);
	return (true);
}
