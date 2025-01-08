/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:28:10 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:41:30 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static bool	handle_complex_collision(t_shape *shape1, t_shape *shape2,
	bool resolve, t_shape *t_s)
{
	bool	did_collide;

	did_collide = false;
	if (shape1->type == SPHERE && shape2->type == CUBE && t_s != shape2)
		did_collide = sphere_box_collision(shape2, shape1, false, resolve);
	else if (shape1->type == CUBE && shape2->type == SPHERE && t_s != shape2)
		did_collide = sphere_box_collision(shape1, shape2, true, resolve);
	else if (shape1->type == CUBE && shape2->type == PLANE)
		did_collide = box_plane_collision(shape1, shape2, resolve);
	else if (shape1->type == CYLINDER && shape2->type == SPHERE
		&& t_s != shape2)
		did_collide = cylinder_sphere_collision(shape1, shape2, resolve);
	else if (shape1->type == SPHERE && shape2->type == CYLINDER
		&& t_s != shape2)
		did_collide = cylinder_sphere_collision(shape2, shape1, resolve);
	else if (shape1->type == CUBE && shape2->type == CYLINDER && t_s != shape2)
		did_collide = box_cylinder_collision(shape1, shape2);
	else if (shape1->type == CYLINDER && shape2->type == CUBE && t_s != shape2)
		did_collide = box_cylinder_collision(shape2, shape1);
	return (did_collide);
}

bool	same_object_collision(t_shape *shape1, t_shape *shape2, bool resolve,
	t_shape *t_s)
{
	bool	did_collide;

	did_collide = false;
	if (shape1->type == SPHERE && shape2->type == SPHERE)
	{
		did_collide = sphere_sphere_collision(shape1, shape2);
		if (did_collide && resolve)
			resolve_sphere_sphere(shape1, shape2, t_s);
	}
	else if (shape1->type == CUBE && shape2->type == CUBE)
	{
		did_collide = box_box_collision(shape1, shape2, false);
		if (did_collide && resolve)
			box_box_collision_resolution(shape1, shape2, t_s);
	}
	else if (shape1->type == CYLINDER && shape2->type == CYLINDER)
		did_collide = cylinder_cylinder_collision(shape1, shape2);
	else if (shape1->type == CONE && shape2->type == CONE)
		did_collide = cone_cone_collision(shape1, shape2);
	return (did_collide);
}

bool	check_collision(t_shape *shape1, t_shape *shape2, bool resolve,
	t_shape *transformed_shape)
{
	bool	did_collide;

	did_collide = false;
	if (shape1->type == shape2->type)
		did_collide = same_object_collision(shape1, shape2, resolve,
				transformed_shape);
	else if (shape1->type == SPHERE && shape2->type == PLANE)
	{
		did_collide = sphere_plane_collision(shape1, shape2);
		if (did_collide && resolve)
			sphere_plane_collision_resolution(shape1, shape2);
	}
	else if (shape1->type == CYLINDER && shape2->type == PLANE)
	{
		did_collide = cylinder_plane_collision(shape1, shape2);
		if (did_collide && resolve)
			cylinder_plane_collision_resolution(shape1, shape2);
	}
	else
		did_collide = handle_complex_collision(shape1, shape2, resolve,
				transformed_shape);
	return (did_collide);
}
