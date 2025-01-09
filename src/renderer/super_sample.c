/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_sample.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:24:44 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/08 17:57:38 by sbartoul         ###   ########.fr       */
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
	//when casting rays for rendering, it's often more accurate to sample the center of the
	//pixel rather than one of its edges. This is because each pixel corresponds to a small area
	//in the scene, and using the center of the pixel helps achieve more precise and smooth sampling,
	//especially when dealing with anti-aliasing or finer details.
	ray_from_cam(&ray, &scene->cam, x + 0.5, y + 0.5);
	shape_idx = -1;
	arr->count = 0;
	while (++shape_idx < scene->count.shapes)
		intersect(&scene->shapes[shape_idx], &ray, arr);
	color = shade_point(arr, scene, &ray);
	set_color(tdata, x, y, create_mlx_color(&color));
	return (color);
}

// supersampling anti-aliasing (SSAA) technique to improve the visual quality of
//the rendered image by smoothing out jagged edge
//Computes the final color for a pixel by averaging color of muliple sub-pixels around it.
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
	//Render Sub-Pixels Around the Main Pixel
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			//Each sub-pixel's coordinates are offset by small fractions (i + 0.5) / 2 and 
			//(j + 0.5) / 2 from the main pixel's coordinates.
			//These offsets simulate sampling at the sub-pixel level.
			color = render_pixel(x + (i + 0.5) / 2, y + (j + 0.5) / 2,
					arr, tdata);
			add_colors(&avg_color, &avg_color, &color);
		}
	}
	//The total color (from the main pixel and 4 sub-pixels) is divided by 5 to calculate the average color.
	mult_color(&avg_color, &avg_color, 1.0 / (5));
	set_color(tdata, x, y, create_mlx_color(&avg_color));
	return (avg_color);
}
