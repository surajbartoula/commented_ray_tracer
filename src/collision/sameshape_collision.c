/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sameshape_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:25:45 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/28 11:52:26 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	sphere_sphere_collision(const t_shape *sphere1, const t_shape *sphere2)
{
	double		distance;
	t_vector	center_diff;

	sub_vector(&center_diff, &sphere1->origin, &sphere2->origin);
	distance = vector_magnitude(&center_diff);
	if (distance <= (sphere1->props.radius + sphere2->props.radius))
		return (true);
	return (false);
}

bool	box_box_collision(t_shape *box1, t_shape *box2, bool resolve)
{
	t_vector	resolution;

	if (resolve == true)
	{
		if (test_box_axes(box1, box2, &resolution) == true)
		{
			add_vector(&box2->origin, &box2->origin, &resolution);
			return (true);
		}
		return (false);
	}
	else if (test_box_axes(box1, box2, NULL) == true)
		return (true);
	return (false);
}

bool	cone_cone_collision(t_shape *co1, t_shape *co2)
{
	if (gjk(co1, co2) == true)
		return (true);
	return (false);
}

bool	cylinder_cylinder_collision(t_shape *cyl1, t_shape *cyl2)
{
	if (gjk(cyl1, cyl2) == true)
		return (true);
	return (false);
}
