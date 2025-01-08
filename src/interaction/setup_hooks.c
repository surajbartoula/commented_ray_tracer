/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:33:51 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:42 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	close_window(t_scene *scene)
{
	free_scene(scene);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_release(int key, t_scene *scene)
{
	toggle_keys_held(key, scene, false);
	return (0);
}

int	key_press(int key, t_scene *scene)
{
	if (key == J)
	{
		scene->settings.supersampling = !scene->settings.supersampling;
		calc_transform(scene);
		render_scene(scene);
	}
	if (key == RETURN && scene->settings.edit_mode == true)
		spawn_shape(scene);
	if (key == T && scene->settings.edit_mode == true)
		toggle_shape(scene);
	if (scene->settings.light_mode == true)
		handle_color_change(key, scene, &scene->lights[scene->light_idx].color);
	else
		handle_color_change(key, scene,
			&scene->shapes[scene->shape_idx].props.color);
	rest_press(key, scene);
	if (key == ESC)
		return (close_window(scene));
	if (!is_toggle_key(key, scene))
		return (0);
	calc_transform(scene);
	render_scene(scene);
	return (0);
}

void	setup_hooks(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->count.shapes && scene->shapes[i].type == PLANE)
		i++;
	if (i == scene->count.shapes && scene->count.shapes > 0)
	{
		scene->shapes[0].props.highlighted = false;
		scene->shape_idx = -1;
	}
	else if (scene->shapes[i].type != PLANE && scene->count.shapes > 0)
	{
		scene->shapes[i].props.highlighted = true;
		scene->shape_idx = i;
	}
	mlx_hook(scene->disp->win, 2, (1L << 0), key_press, scene);
	mlx_hook(scene->disp->win, 3, (1L << 1), key_release, scene);
	mlx_hook(scene->disp->win, 4, (1L << 2), mouse_down, scene);
	mlx_hook(scene->disp->win, 5, (1L << 3), mouse_up, scene);
	mlx_hook(scene->disp->win, 17, 0, close_window, scene);
	mlx_loop_hook(scene->disp->mlx, render_loop, scene);
}
