/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:08:22 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/05 18:42:32 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	project_on_screen(t_scene *scene, t_shape *shape)
{
	t_vector	p_from_origin;

	mat_vec_mult(&p_from_origin, &scene->cam.transform, &shape->origin);
	perspective_projection(&p_from_origin, scene);
	if (shape->type == SPHERE || shape->type == CYLINDER || shape->type == CUBE
		|| shape->type == CONE)
	{
		if (p_from_origin.z < 0)
			render_marker(scene, p_from_origin.x * scene->settings.disp_w,
				p_from_origin.y * scene->settings.disp_h, 0x00ffff);
		mlx_put_image_to_window(scene->disp->mlx, scene->disp->win,
			scene->disp->display_img, 0, 0);
	}
}

void	render_shape(t_scene *scene)
{
	int		shape_idx;
	t_shape	*shape;

	shape_idx = 0;
	if (scene->settings.edit_mode == false)
		return ;
	while (shape_idx < scene->count.shapes)
	{
		shape = &scene->shapes[shape_idx];
		if (shape->props.highlighted == false)
		{
			shape_idx++;
			continue ;
		}
		project_on_screen(scene, shape);
		return ;
	}
}
