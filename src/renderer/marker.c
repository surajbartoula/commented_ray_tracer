/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:13:21 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/29 19:17:39 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	draw_marker(t_scene *scene, int x, int y, int color)
{
	char	*d;
	int		w;

	w = scene->settings.disp_w;
	if (x <= 0 || y <= 0 || x >= w || y >= scene->settings.disp_h)
		return ;
	d = scene->disp->display_addr + (y * w + x) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + ((y + 1) * w + x) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + ((y - 1) * w + x) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + (y * w + x + 1) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + ((y + 1) * w + x + 1) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + ((y - 1) * w + x + 1) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + (y * w + x - 1) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + ((y - 1) * w + x - 1) * scene->disp->bpp;
	*(unsigned int *)d = color;
	d = scene->disp->display_addr + ((y + 1) * w + x - 1) * scene->disp->bpp;
	*(unsigned int *)d = color;
}

void	project_marker_on_screen(t_scene *scene, t_shape *shape)
{
	t_vector	origin_proj;

	mat_vec_mult(&origin_proj, &scene->cam.transform, &shape->origin);
	perspective_projection(&origin_proj, scene);
	if (shape->type == SPHERE || shape->type == CYLINDER || shape->type == CUBE
		|| shape->type == CONE)
	{
		if (origin_proj.z < 0)
			draw_marker(scene, origin_proj.x * scene->settings.disp_w,
				origin_proj.y * scene->settings.disp_h, 0x00ffff);
		mlx_put_image_to_window(scene->disp->mlx, scene->disp->win,
			scene->disp->display_img, 0, 0);
	}
}

void	render_shape_marker(t_scene *scene)
{
	int			shape_idx;
	t_shape		*shape;

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
		project_marker_on_screen(scene, shape);
		return ;
	}
}
