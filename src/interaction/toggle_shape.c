/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:57:52 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:59:04 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	toggle_reflections(t_scene *scene)
{
	if (scene->settings.reflection_depth == 0)
		scene->settings.reflection_depth = REFLECTION_DEPTH;
	else if (scene->settings.reflection_depth != 0)
		scene->settings.reflection_depth = 0;
}

void	toggle_shape_properties(t_shape *shape)
{
	if (shape->type == SPHERE)
		shape->type = CUBE;
	else if (shape->type == CUBE)
	{
		shape->props.height = 1;
		shape->props.scale.y = 1;
		shape->props.radius = shape->props.scale.x;
		shape->type = CYLINDER;
	}
	else if (shape->type == CYLINDER)
	{
		shape->props.height = shape->props.scale.y * 2;
		shape->props.scale.y = 1;
		shape->props.radius = shape->props.scale.x;
		shape->type = CONE;
	}
	else if (shape->type == CONE)
		shape->type = SPHERE;
}

void	toggle_shape(t_scene *scene)
{
	t_shape	*shape;

	shape = &scene->shapes[scene->shape_idx];
	shape->props.radius = max(shape->props.radius, 0.5);
	shape->props.radius_squared = shape->props.radius * shape->props.radius;
	shape->props.height = max(shape->props.height, 0.5);
	shape->props.scale.x = shape->props.radius;
	shape->props.scale.y = shape->props.radius;
	shape->props.scale.z = shape->props.radius;
	ft_bzero(&shape->orientation, sizeof(t_vector));
	shape->orientation.y = 1;
	identity_matrix(&shape->added_rots);
	toggle_shape_properties(shape);
}
