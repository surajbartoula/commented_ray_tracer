/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:17:53 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 22:33:03 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rotate_x(t_scene *scene, t_mat4 *rot_mat, double deg)
{
	t_mat4		rot;
	t_vector	ax;
	t_vector	up;
	t_mat4		mat_copy;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	up.w = 0;
	cross_product(&ax, &up, &scene->cam.dir);
	normalize_vector(&ax);
	if (scene->keys_held.down == true)
		matrix_rotate_axis(&rot, &ax, -deg);
	else
		matrix_rotate_axis(&rot, &ax, deg);
	ft_memcpy(&mat_copy, rot_mat, sizeof(t_mat4));
	matrix_multiply(rot_mat, &rot, &mat_copy);
}

void	rotate_y(t_scene *scene, t_mat4 *rot_mat, double deg)
{
	t_mat4	rot;
	t_mat4	mat_copy;

	if (scene->keys_held.left == true)
		matrix_rotate_yaxis(&rot, deg);
	else
		matrix_rotate_yaxis(&rot, -deg);
	ft_memcpy(&mat_copy, rot_mat, sizeof(t_mat4));
	matrix_multiply(rot_mat, &rot, &mat_copy);
}

void	rotate_z(t_scene *scene, t_mat4 *rot_mat, double deg)
{
	t_mat4	rot;
	t_mat4	mat_copy;

	if (scene->keys_held.left == true)
		matrix_rotate_axis(&rot, &scene->cam.dir, deg);
	else
		matrix_rotate_axis(&rot, &scene->cam.dir, -deg);
	ft_memcpy(&mat_copy, rot_mat, sizeof(t_mat4));
	matrix_multiply(rot_mat, &rot, &mat_copy);
}

void	rotate_object(t_scene *scene)
{
	if (scene->keys_held.shift == false
		&& (scene->keys_held.left == true || scene->keys_held.right == true))
		rotate_y(scene, &scene->shapes[scene->shape_idx].added_rots,
			DEG_TO_RAD * 5);
	if (scene->keys_held.shift == true
		&& (scene->keys_held.left == true || scene->keys_held.right == true))
		rotate_z(scene, &scene->shapes[scene->shape_idx].added_rots,
			DEG_TO_RAD * 5);
	if (scene->keys_held.up == true || scene->keys_held.down == true)
		rotate_x(scene, &scene->shapes[scene->shape_idx].added_rots,
			DEG_TO_RAD * 5);
}
