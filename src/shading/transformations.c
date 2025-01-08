/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:43:05 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/04 11:25:02 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	intersect(t_shape *shape, const t_ray *ray, t_intersections *xs)
{
	t_ray	transf_ray;

	if (xs->count >= 200)
		return (false);
	if (shape->type == SPHERE)
		return (intersect_sphere_fast(ray, xs, shape));
	if (shape->type == PLANE)
		return (intersect_plane_fast(ray, shape, xs));
	transform_ray(&transf_ray, ray, shape);
	if (shape->type == CYLINDER)
		return (intersect_cylinder(&transf_ray, shape, xs));
	if (shape->type == CONE)
		return (intersect_cone(&transf_ray, shape, xs));
	else if (shape->type == CUBE)
		return (intersect_cube(shape, &transf_ray, xs));
	return (false);
}
