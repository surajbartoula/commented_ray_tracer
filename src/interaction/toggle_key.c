/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:47:59 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:57 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	toggle_edit_mode(int key, t_scene *scene)
{
	if (key == SPACE)
		scene->settings.edit_mode = !scene->settings.edit_mode;
}

void	toggle_keys_continue(int key, t_scene *scene, bool onoff)
{
	if (key == W)
		scene->keys_held.w = onoff;
	if (key == A)
		scene->keys_held.a = onoff;
	if (key == S)
		scene->keys_held.s = onoff;
	if (key == D)
		scene->keys_held.d = onoff;
	if (key == UP)
		scene->keys_held.up = onoff;
	if (key == DOWN)
		scene->keys_held.down = onoff;
	if (key == LEFT)
		scene->keys_held.left = onoff;
	if (key == RIGHT)
		scene->keys_held.right = onoff;
}

void	toggle_keys_held(int key, t_scene *scene, bool onoff)
{
	if (key == Q)
		scene->keys_held.q = onoff;
	if (key == E)
		scene->keys_held.e = onoff;
	if (key == PLUS)
		scene->keys_held.plus = onoff;
	if (key == MINUS)
		scene->keys_held.minus = onoff;
	if (key == SHIFT)
		scene->keys_held.shift = onoff;
	if (key == X)
		scene->keys_held.x = onoff;
	if (key == Y)
		scene->keys_held.y = onoff;
	if (key == Z)
		scene->keys_held.z = onoff;
	if (key == O)
		scene->keys_held.o = onoff;
	toggle_keys_continue(key, scene, onoff);
}

bool	is_toggle_key(int key, t_scene *scene)
{
	return (key == SPACE || key == R
		|| (scene->settings.edit_mode == true
			&& (key == RETURN || key == ONE_KEY || key == TWO_KEY
				|| key == THREE_KEY || key == FOUR_KEY
				|| key == FIVE_KEY || key == SIX_KEY
				|| key == TAB || key == C || key == T
				|| key == P || key == L || key == H)));
}
