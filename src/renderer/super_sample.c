/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_sample.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:24:44 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/02 19:44:49 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_color	render_pixel(double x, double y, t_intersections *arr,
	t_thread_data *tdata)
{
	int		shape_idx;
	t_scene	*scene;
	t_ray	ray;
	t_color	color;

	set_color(tdata, x, y, 0);
	scene = tdata->scene;
	ray_from_cam(&ray, &scene->cam, x + 0.5, y + 0.5);
	shape_idx = -1;
	arr->count = 0;
	while (++shape_idx < scene->count.shapes)
		intersect(&scene->shapes[shape_idx], &ray, arr);
	color = shade_point(arr, scene, &ray);
	set_color(tdata, x, y, create_mlx_color(&color));
	return (color);
}

t_color	super_sample_pixel(double x, double y, t_intersections *arr,
			t_thread_data *tdata)
{
	int				i;
	int				j;
	t_color			color;
	t_color			avg_color;

	if (tdata->scene->settings.supersampling == false
		|| tdata->scene->settings.edit_mode == false)
		return (render_pixel(x, y, arr, tdata));
	ft_bzero(&avg_color, sizeof(t_color));
	color = render_pixel(x, y, arr, tdata);
	add_colors(&avg_color, &avg_color, &color);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			color = render_pixel(x + (i + 0.5) / 2, y + (j + 0.5) / 2,
					arr, tdata);
			add_colors(&avg_color, &avg_color, &color);
		}
	}
	mult_color(&avg_color, &avg_color, 1.0 / (5));
	set_color(tdata, x, y, create_mlx_color(&avg_color));
	return (avg_color);
}
