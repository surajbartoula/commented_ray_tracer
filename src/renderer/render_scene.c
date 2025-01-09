/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:02:22 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/08 17:54:00 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	render_shape_info(t_scene *scene)
{
	int			shape_idx;
	t_shape		*shape;
	t_vector	origin;

	shape_idx = -1;
	if (scene->settings.edit_mode == false)
		return ;
	while (++shape_idx < scene->count.shapes)
	{
		shape = &scene->shapes[shape_idx];
		if (shape->props.highlighted == false)
			continue ;
		origin = get_origin(shape, scene);
		if (origin.z > 0)
			return ;
		perspective_projection(&origin, scene);
		if (shape->type == SPHERE || shape->type == CYLINDER
			|| shape->type == CUBE || shape->type == CONE)
		{
			draw_shape_type(scene, shape, &origin);
			draw_shape_coordinates(shape, scene, &origin);
			draw_shape_properties(shape, scene, &origin);
		}
	}
}

void	*scale_adjacent(t_thread_data *tdata)
{
	int	i_w;
	int	j_h;
	int	h;
	int	w;

	j_h = tdata->y_scale_start - 1;
	while (++j_h < tdata->y_scale_end)
	{
		i_w = -1;
		while (++i_w < tdata->scene->settings.disp_w)
		{
			w = round((i_w / (double)tdata->scene->settings.disp_w)
					* tdata->width);
			h = round((j_h / (double)tdata->scene->settings.disp_h)
					* tdata->height);
			w = min(w, tdata->width - 1);
			h = min(h, tdata->height - 1);
			*(unsigned int *)(tdata->scene->disp->display_addr
					+ (j_h * tdata->scene->settings.disp_w + i_w)
					* tdata->scene->disp->bpp) = *(unsigned int *)(tdata->addr
					+ (h * tdata->width + w) * tdata->scene->disp->bpp);
		}
	}
	return (NULL);
}

void	*renderwith_threads(t_thread_data *tdata)
{
	int				x;
	int				y;
	t_intersections	arr;

	y = tdata->y_start;
	while (y < tdata->y_end)
	{
		x = 0;
		while (x < tdata->width)
		{
			set_color(tdata, x, y, 0);
			render_pixel(x, y, &arr, tdata);
			x += 3;
		}
		y += 3;
	}
	//Higher Thresholds (e.g., 50): Reduce the number of supersampled pixels, improving performance but potentially leaving visible artifacts.
	//Lower Thresholds (e.g., 10): Increase the number of supersampled pixels, enhancing quality but increasing computational overhead.
	//25 is a reasonable compromise that balances rendering quality with performance.
	fill_h(tdata, 25);
	fill_v(tdata, 25);
	return (NULL);
}

void	render_scene(t_scene *scene)
{
	t_thread_data	tdata[NUM_THREADS];

	init_thread_data(tdata, scene);
	exec_thread(tdata, renderwith_threads);
	exec_thread(tdata, scale_adjacent);
	mlx_put_image_to_window(scene->disp->mlx, scene->disp->win,
		scene->disp->display_img, 0, 0);
	render_shape_marker(scene);
	if (scene->settings.light_mode == true)
	{
		project_rays_on_screen(scene);
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			scene->settings.disp_w * .9, 20, 0xffffff, "LIGHT MODE");
	}
	else if (scene->settings.camera_mode == false)
		render_shape_info(scene);
}
