/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:46:16 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/05 18:39:58 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	fill_zero(t_vector *vec_x, t_vector *vec_y, t_vector *vec_z)
{
	ft_bzero(vec_x, sizeof(t_vector));
	ft_bzero(vec_y, sizeof(t_vector));
	ft_bzero(vec_z, sizeof(t_vector));
}

void	move_cam(t_scene *scene)
{
	t_vector	vec_x;
	t_vector	vec_y;
	t_vector	vec_z;

	fill_zero(&vec_x, &vec_y, &vec_z);
	if (scene->keys_held.w == true)
		sphere_mod(&vec_z, scene->cam.pi, scene->cam.theta, CAM_SPEED);
	if (scene->keys_held.s == true)
		sphere_mod(&vec_z, scene->cam.pi, scene->cam.theta, -CAM_SPEED);
	if (scene->keys_held.a == true)
		sphere_mod(&vec_x, M_PI_2, scene->cam.theta - M_PI_2, -CAM_SPEED);
	if (scene->keys_held.d == true)
		sphere_mod(&vec_x, M_PI_2, scene->cam.theta - M_PI_2, CAM_SPEED);
	if (scene->keys_held.q == true)
		vec_y.y = 0.35;
	if (scene->keys_held.e == true)
		vec_y.y = -0.35;
	if (scene->keys_held.w == true || scene->keys_held.a == true
		|| scene->keys_held.s == true || scene->keys_held.d == true
		|| scene->keys_held.q == true || scene->keys_held.e == true)
	{
		add_vector(&scene->cam.pos, &scene->cam.pos, &vec_x);
		add_vector(&scene->cam.pos, &scene->cam.pos, &vec_y);
		add_vector(&scene->cam.pos, &scene->cam.pos, &vec_z);
	}
}

void	camera_controls(t_scene *scene)
{
	if (scene->keys_held.w || scene->keys_held.a || scene->keys_held.s
		|| scene->keys_held.d || scene->keys_held.q || scene->keys_held.e)
		move_cam(scene);
	if (scene->keys_held.up == true && scene->cam.pi > 0.2)
		scene->cam.pi -= 0.05;
	if (scene->keys_held.down == true && scene->cam.pi < M_PI - 0.2)
		scene->cam.pi += 0.05;
	if (scene->keys_held.left == true)
		scene->cam.theta += 0.10;
	if (scene->keys_held.right == true)
		scene->cam.theta -= 0.10;
	if (scene->keys_held.up || scene->keys_held.left || scene->keys_held.right
		|| scene->keys_held.down)
		sphere_mod(&scene->cam.dir, scene->cam.pi,
			scene->cam.theta, 1);
}
