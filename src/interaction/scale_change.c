/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:53:52 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:34 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	scale_cube_sides(t_scene *scene, t_shape *shape)
{
	if (shape->type != CUBE)
		return ;
	if (scene->keys_held.shift == false)
	{
		if (scene->keys_held.x)
			shape->props.scale.x += 0.05;
		if (scene->keys_held.y)
			shape->props.scale.y += 0.05;
		if (scene->keys_held.z)
			shape->props.scale.z += 0.05;
	}
	if (scene->keys_held.shift == true)
	{
		if (scene->keys_held.x && shape->props.scale.x > 0.3)
			shape->props.scale.x -= 0.05;
		if (scene->keys_held.y && shape->props.scale.y > 0.3)
			shape->props.scale.y -= 0.05;
		if (scene->keys_held.z && shape->props.scale.z > 0.3)
			shape->props.scale.z -= 0.05;
	}
}

void	scale_object(t_scene *scene, t_shape *shape)
{
	double	increment;

	increment = 0.04;
	if (scene->keys_held.minus == true)
		increment *= -1;
	if (shape->type == CUBE)
	{
		if (shape->props.scale.x > 0.3 || !scene->keys_held.minus)
			shape->props.scale.x += increment;
		if (shape->props.scale.y > 0.3 || !scene->keys_held.minus)
			shape->props.scale.y += increment;
		if (shape->props.scale.z > 0.3 || !scene->keys_held.minus)
			shape->props.scale.z += increment;
	}
	else
	{
		if (shape->props.radius > 0.3 || !scene->keys_held.minus)
			shape->props.radius += increment;
		shape->props.scale.x = shape->props.radius;
		shape->props.scale.y = shape->props.radius;
		if (shape->type == CYLINDER || shape->type == CONE)
			shape->props.scale.y = 1;
		shape->props.scale.z = shape->props.radius;
	}
	shape->props.radius_squared = shape->props.radius * shape->props.radius;
}

void	change_height(t_scene *scene, t_shape *shape)
{
	if (scene->keys_held.plus == true)
	{
		shape->props.height += 0.04;
	}
	if (scene->keys_held.minus == true)
	{
		if (shape->props.height > 0.2)
			shape->props.height -= 0.04;
	}
}
