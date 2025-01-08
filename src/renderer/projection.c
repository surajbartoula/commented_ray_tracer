/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:58:30 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:54:34 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	render_marker(t_scene *scene, int x, int y, int color)
{
	char	*str;
	int		w;

	w = scene->settings.disp_w;
	if (x <= 0 || y <= 0 || x >= w || y >= scene->settings.disp_h)
		return ;
	str = scene->disp->display_addr + (y * w + x) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + ((y + 1) * w + x) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + ((y - 1) * w + x) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + (y * w + x + 1) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + ((y + 1) * w + x + 1) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + (y - 1 * w + x + 1) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + (y * w + x - 1) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + (y - 1 * w + x - 1) * scene->disp->bpp;
	*(unsigned int *)str = color;
	str = scene->disp->display_addr + ((y + 1) * w + x - 1) * scene->disp->bpp;
	*(unsigned int *)str = color;
}

void	perspective_projection(t_vector *point, const t_scene *scene)
{
	point->x /= -point->z;
	point->y /= -point->z;
	point->x = (point->x + scene->cam.half_w)
		/ (scene->cam.half_w * 2);
	point->y = (point->y + scene->cam.half_h)
		/ (scene->cam.half_h * 2);
	point->x = 1 - point->x;
	point->y = 1 - point->y;
}

void	project_rays_on_screen(t_scene *scene)
{
	t_vector	origin;
	t_light		*light;

	light = &scene->lights[scene->light_idx];
	mat_vec_mult(&origin, &scene->cam.transform, &light->position);
	perspective_projection(&origin, scene);
	if (origin.z < 0)
		render_marker(scene, origin.x * scene->settings.disp_w,
			origin.y * scene->settings.disp_h, 0x00ffff);
	mlx_put_image_to_window(scene->disp->mlx, scene->disp->win,
		scene->disp->display_img, 0, 0);
}
