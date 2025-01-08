/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:14:47 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:06 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	collide_after_transform(t_scene *scene)
{
	if (scene->settings.collisions && (scene->keys_held.w
			|| scene->keys_held.a || scene->keys_held.s || scene->keys_held.d
			|| scene->keys_held.up || scene->keys_held.right
			|| scene->keys_held.q || scene->keys_held.e || scene->keys_held.down
			|| scene->keys_held.left || scene->keys_held.plus
			|| scene->keys_held.minus || scene->keys_held.x
			|| scene->keys_held.y || scene->keys_held.z))
		collided(scene, true, 10, &scene->shapes[scene->shape_idx]);
}

void	transform_object(t_scene *scene)
{
	if (scene->keys_held.w == true || scene->keys_held.s == true)
		move_object_fwd(scene, &scene->shapes[scene->shape_idx]);
	if (scene->keys_held.a == true || scene->keys_held.d == true)
		move_object_h(scene, &scene->shapes[scene->shape_idx]);
	if (scene->keys_held.q == true || scene->keys_held.e == true)
		move_object_v(scene, &scene->shapes[scene->shape_idx]);
	if (scene->keys_held.shift == false
		&& (scene->keys_held.plus || scene->keys_held.minus))
		scale_object(scene, &scene->shapes[scene->shape_idx]);
	if (scene->keys_held.shift == true
		&& (scene->keys_held.plus == true || scene->keys_held.minus == true))
		change_height(scene, &scene->shapes[scene->shape_idx]);
	if (scene->keys_held.shift == false
		&& (scene->keys_held.x || scene->keys_held.y || scene->keys_held.z))
		scale_cube_sides(scene, &scene->shapes[scene->shape_idx]);
	if (scene->keys_held.shift == true
		&& (scene->keys_held.x || scene->keys_held.y || scene->keys_held.z))
		scale_cube_sides(scene, &scene->shapes[scene->shape_idx]);
	rotate_object(scene);
	collide_after_transform(scene);
}
