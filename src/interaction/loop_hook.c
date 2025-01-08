/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:02:42 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:13 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	is_loop_hook_key(t_scene *scene)
{
	return (scene->keys_held.w || scene->keys_held.a || scene->keys_held.s
		|| scene->keys_held.d || scene->keys_held.up
		|| scene->keys_held.right || scene->keys_held.q
		|| scene->keys_held.e || scene->keys_held.down
		|| scene->keys_held.left || scene->keys_held.plus
		|| scene->keys_held.minus || scene->keys_held.x
		|| scene->keys_held.y || scene->keys_held.z);
}

int	render_loop(t_scene *scene)
{
	if (scene->settings.camera_mode == true
		&& scene->settings.edit_mode == true)
		camera_controls(scene);
	else if (scene->settings.edit_mode && !scene->settings.light_mode)
	{
		transform_object(scene);
		mouse_rotate(scene);
		mouse_move(scene);
	}
	else if (scene->settings.edit_mode && scene->settings.light_mode)
		light_controls(scene);
	if (scene->keys_held.o && scene->settings.edit_mode \
		&& !scene->look_at.trigger)
		look_at(scene, &scene->shapes[scene->shape_idx]);
	if (scene->look_at.trigger == true && scene->settings.edit_mode == true)
		look_at_animation(scene);
	if (scene->settings.edit_mode == true
		&& is_loop_hook_key(scene))
	{
		calc_transform(scene);
		render_scene(scene);
	}
	return (0);
}
