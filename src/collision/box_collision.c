/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:14:09 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/30 14:06:51 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	calculate_extent(const t_shape *box, const t_vector *plane_normal)
{
	double	extent;

	extent = 0.0;
	extent += box->props.scale.x * fabs(dot_product(plane_normal,
				&(t_vector){box->added_rots[0][0], box->added_rots[1][0],
				box->added_rots[2][0], 0}));
	extent += box->props.scale.y * fabs(dot_product(plane_normal,
				&(t_vector){box->added_rots[0][1], box->added_rots[1][1],
				box->added_rots[2][1], 0}));
	extent += box->props.scale.z * fabs(dot_product(plane_normal,
				&(t_vector){box->added_rots[0][2], box->added_rots[1][2],
				box->added_rots[2][2], 0}));
	return (extent);
}

bool	box_plane_collision(t_shape *box, const t_shape *plane, bool resolve)
{
	double		extent;
	double		center_to_plane;
	t_vector	res;

	extent = calculate_extent(box, &plane->orientation);
	center_to_plane = dot_product(&box->origin, &plane->orientation)
		- plane->props.distance_from_origin;
	if (center_to_plane > extent || center_to_plane < -extent)
		return (false);
	if (resolve)
	{
		res = plane->orientation;
		if (center_to_plane < 0)
		{
			scale_vector(&res, &res, extent - fabs(center_to_plane));
			sub_vector(&box->origin, &box->origin, &res);
		}
		else
		{
			scale_vector(&res, &res, extent - center_to_plane);
			add_vector(&box->origin, &box->origin, &res);
		}
	}
	return (true);
}

bool	box_cylinder_collision(t_shape *box, t_shape *cylinder)
{
	return (gjk(box, cylinder));
}
