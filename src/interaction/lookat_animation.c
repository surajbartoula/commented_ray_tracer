/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:00:32 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:57:51 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	reset_look_at(t_scene *scene)
{
	if (scene->cam.dir.x > 0)
		scene->cam.theta = atan(scene->cam.dir.z / scene->cam.dir.x);
	else if (scene->cam.dir.x < 0 && scene->cam.dir.z >= 0)
		scene->cam.theta = atan(scene->cam.dir.z / scene->cam.dir.x) + M_PI;
	else if (scene->cam.dir.x < 0 && scene->cam.dir.z < 0)
		scene->cam.theta = atan(scene->cam.dir.z / scene->cam.dir.x) - M_PI;
	scene->cam.pi = acos(scene->cam.dir.y);
	scene->look_at.trigger = false;
	scene->look_at.step_num = 0;
}

void	look_at_animation(t_scene *scene)
{
	t_vector	pos_step;
	t_vector	dir_step;

	scale_vector(&pos_step, &scene->look_at.pos_diff,
		1.0 / scene->look_at.step_amount);
	scale_vector(&dir_step, &scene->look_at.dir_diff,
		1.0 / scene->look_at.step_amount);
	add_vector(&scene->cam.pos, &scene->cam.pos, &pos_step);
	add_vector(&scene->look_at.current_dir, &scene->look_at.current_dir,
		&dir_step);
	scene->cam.dir = scene->look_at.current_dir;
	calc_transform(scene);
	render_scene(scene);
	scene->look_at.step_num++;
	if (scene->look_at.step_num >= scene->look_at.step_amount)
		reset_look_at(scene);
}
