/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:33:40 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/02 16:16:54 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	fill_skippedpixelh(double x, double y, t_thread_data *tdata, int th)
{
	int				i;
	int				j;
	t_intersections	arr;

	i = get_color(tdata, x - 1, y);
	j = get_color(tdata, x + 2, y);
	if (color_diff(i, j) > th)
	{
		if (tdata->scene->settings.supersampling == true)
			super_sample_pixel(x - 1, y, &arr, tdata);
		super_sample_pixel(x, y, &arr, tdata);
		super_sample_pixel(x + 1, y, &arr, tdata);
		if (tdata->scene->settings.supersampling == true)
			super_sample_pixel(x + 2, y, &arr, tdata);
	}
	else
	{
		set_color(tdata, x, y, mix_color(i, j, 2.0 / 3.0));
		set_color(tdata, x + 1, y, mix_color(i, j, 2.0 / 3.0));
	}
}

void	fill_skippedpixelv(double x, double y, t_thread_data *tdata, int th)
{
	int				i;
	int				j;
	t_intersections	arr;

	i = get_color(tdata, x, y - 1);
	if (y + 2 >= tdata->y_end && y < tdata->y_end)
		super_sample_pixel(x, y, &arr, tdata);
	if (y + 2 >= tdata->y_end && (y + 1) < tdata->y_end)
		super_sample_pixel(x, y + 1, &arr, tdata);
	if (y + 2 >= tdata->y_end)
		return ;
	j = get_color(tdata, x, y + 2);
	if (color_difference(i, j) > th)
	{
		super_sample_pixel(x, y - 1, &arr, tdata);
		super_sample_pixel(x, y, &arr, tdata);
		super_sample_pixel(x, y + 1, &arr, tdata);
		super_sample_pixel(x, y + 2, &arr, tdata);
	}
	else
	{
		set_color(tdata, x, y, mix_color(i, j, 2.0 / 3.0));
		set_color(tdata, x, y + 1, mix_color(i, j, 1.0 / 3.0));
	}
}

void	fill_h(t_thread_data *tdata, int th)
{
	int	x;
	int	y;

	y = tdata->y_start - 1;
	while (++y < tdata->y_end)
	{
		x = 1;
		while (x < tdata->width)
		{
			if (x + 2 < tdata->width)
				fill_skippedpixelh(x, y, tdata, th);
			else
			{
				if (x < tdata->width)
					set_color(tdata, x, y, get_color(tdata, x - 1, y));
				if (x + 1 < tdata->width)
					set_color(tdata, x + 1, y, get_color(tdata, x, y));
			}
			x += 3;
		}
	}
}

void	fill_v(t_thread_data *tdata, int th)
{
	int	x;
	int	y;

	y = tdata->y_start + 1;
	while (y < tdata->y_end)
	{
		x = 1;
		while (x < tdata->width)
		{
			if (y + 2 < tdata->width)
				fill_skippedpixelv(x, y, tdata, th);
			else
			{
				if (y < tdata->height)
					set_color(tdata, x, y, get_color(tdata, x, y - 1));
				if (y + 1 < tdata->height)
					set_color(tdata, x, y + 1, get_color(tdata, x, y));
			}
			x++;
		}
		y += 3;
	}
}
