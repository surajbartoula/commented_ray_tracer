/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:51:39 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:48 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	default_shape_props(t_props *props)
{
	ft_bzero(&props->color, sizeof(t_color));
	props->diffuse = 0.9;
	props->highlighted = true;
	props->radius = 0.7;
	props->radius_squared = 0.7 * 0.7;
	props->scale.x = 0.7;
	props->scale.y = 0.7;
	props->scale.z = 0.7;
	props->reflectiveness = 0.2;
	props->shininess = 50;
	props->specular = 0.8;
}

void	spawn_shape(t_scene *scene)
{
	if (scene->count.shapes >= SHAPE_MAX - 1)
		return ;
	scene->shapes[scene->shape_idx].props.highlighted = false;
	scene->shapes[scene->count.shapes].origin.x = scene->cam.dir.x * 5 \
		+ scene->cam.pos.x;
	scene->shapes[scene->count.shapes].origin.y = scene->cam.dir.y + \
		scene->cam.pos.y;
	scene->shapes[scene->count.shapes].origin.z = scene->cam.dir.z * 5 + \
		scene->cam.pos.z;
	scene->shapes[scene->count.shapes].origin.w = 1;
	default_shape_props(&scene->shapes[scene->count.shapes].props);
	scene->shapes[scene->count.shapes].type = SPHERE;
	scene->shapes[scene->count.shapes].id = scene->count.shapes;
	ft_bzero(&scene->shapes[scene->count.shapes].orientation, sizeof(t_vector));
	scene->shapes[scene->count.shapes].orientation.y = 1;
	identity_matrix(&scene->shapes[scene->count.shapes].added_rots);
	scene->count.shapes++;
	scene->shape_idx = scene->count.shapes - 1;
}

void	select_shape(int key, t_scene *scene)
{
	if (key == TAB && scene->settings.edit_mode == true
		&& scene->settings.light_mode == false)
	{
		scene->shapes[scene->shape_idx].props.highlighted = false;
		scene->shape_idx = (scene->shape_idx + 1) % scene->count.shapes;
		while (scene->shapes[scene->shape_idx].type == PLANE)
			scene->shape_idx = (scene->shape_idx + 1) % scene->count.shapes;
		scene->shapes[scene->shape_idx].props.highlighted = true;
	}
}
