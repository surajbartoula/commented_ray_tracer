/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:02:30 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/07 10:08:25 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//The function transform_view constructs a view transformation matrix for a 3D camera. This matrix defines
//how to transform objects in the world so that they align with the camera's perspective
void	transform_view(t_mat4 *result, const t_vector *from, const t_vector *up,
		const t_vector *forward)
{
	t_vector	left;
	t_vector	true_up;
	t_vector	upn;
	t_mat4		orientation;
	t_mat4		translation;

	upn = *up;
	normalize_vector(&upn);
	cross_product(&left, forward, &upn);
	normalize_vector(&left);
	cross_product(&true_up, &left, forward);
	normalize_vector(&true_up);
	ft_bzero(&orientation, sizeof(t_mat4));
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = -forward->x;
	orientation[2][1] = -forward->y;
	orientation[2][2] = -forward->z;
	orientation[3][3] = 1;
	matrix_translation(&translation, -from->x, -from->y, -from->z);
	matrix_multiply(result, &orientation, &translation);
}

void	calc_cam_transform(t_scene *scene)
{
	t_vector	from;
	t_vector	up;

	from.x = scene->cam.pos.x;
	from.y = scene->cam.pos.y;
	from.z = scene->cam.pos.z;
	from.w = 1; //treated as point not vector
	normalize_vector(&scene->cam.dir);
	up.x = 0;
	up.y = 1;
	up.z = 0;
	up.w = 0;
	//Calculates the view transformation matrix for the camera, aligning the camera's
	//coordinate system with the world coordinate system.
	transform_view(&scene->cam.transform, &from, &up, &scene->cam.dir);
	//The inverse transformation matrix is often needed for operations like transforming rays
	//or objects from camera space back to world space.
	inverse_matrix(&scene->cam.inv_trans, &scene->cam.transform);
}

void	camera_init(t_camera *camera, t_scene *scene)
{
	double	half_view;
	double	aspect;
	double	h;
	double	w;

	h = scene->settings.render_h;
	w = scene->settings.render_w;
	if (scene->settings.edit_mode == true)
	{
		h = scene->settings.edit_h;
		w = scene->settings.edit_w;
	}
	half_view = tan((camera->fov / 2.0f) * M_PI / 180.0f);
	//M_PI / 180 convert degree to radians
	aspect = w / h;
	if (aspect >= 1)
	{
		camera->half_w = half_view;
		camera->half_h = half_view / aspect;
	}
	else
	{
		camera->half_w = half_view * aspect;
		camera->half_h = half_view;
	}
	camera->pixel_sz = (camera->half_w * 2) / w;
}
