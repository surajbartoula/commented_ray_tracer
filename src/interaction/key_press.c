/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:00:43 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:57:37 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rest_press(int key, t_scene *scene)
{
	toggle_edit_mode(key, scene);
	select_shape(key, scene);
	if (key == R)
		toggle_reflections(scene);
	if (key == L)
		scene->settings.light_mode = !scene->settings.light_mode;
	if (key == TAB && scene->settings.edit_mode
		&& scene->settings.light_mode)
		scene->light_idx = (scene->light_idx + 1) % scene->count.lights;
	if (key == P)
	{
		scene->shapes[scene->shape_idx].props.pattern_type += 1;
		scene->shapes[scene->shape_idx].props.pattern_type %= 5;
	}
	if (key == C && scene->settings.edit_mode == true)
		scene->settings.camera_mode = !scene->settings.camera_mode;
	toggle_keys_held(key, scene, true);
	if (key == SPACE || key == R)
		camera_init(&scene->cam, scene);
}

void	handle_color_change(int key, t_scene *scene, t_color *color)
{
	if ((key != ONE_KEY && key != TWO_KEY && key != THREE_KEY && key != FOUR_KEY
			&& key != FIVE_KEY && key != SIX_KEY)
		|| scene->settings.edit_mode == false)
		return ;
	if (key == ONE_KEY && (color->r + 10 / 255.0) < 1)
		color->r += 10 / 255.0;
	if (key == TWO_KEY && (color->r - 10 / 255.0) > 0)
		color->r -= 10 / 255.0;
	if (key == THREE_KEY && (color->g + 10 / 255.0) < 1)
		color->g += 10 / 255.0;
	if (key == FOUR_KEY && (color->g - 10 / 255.0) > 0)
		color->g -= 10 / 255.0;
	if (key == FIVE_KEY && (color->b + 10 / 255.0) < 1)
		color->b += 10 / 255.0;
	if (key == SIX_KEY && (color->b - 10 / 255.0) > 0)
		color->b -= 10 / 255.0;
}
