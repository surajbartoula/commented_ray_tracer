/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:22:05 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:55:01 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	init_thread_data(t_thread_data *tdata, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		tdata[i].height = scene->settings.render_h;
		tdata[i].width = scene->settings.render_w;
		tdata[i].addr = scene->disp->render_addr;
		if (scene->settings.edit_mode == true)
		{
			tdata[i].height = scene->settings.edit_h;
			tdata[i].width = scene->settings.edit_w;
			tdata[i].addr = scene->disp->edit_addr;
		}
		tdata[i].max_tid = NUM_THREADS;
		tdata[i].tid = i;
		tdata[i].scene = scene;
		tdata[i].y_start = (tdata[i].height / (double)NUM_THREADS) * i;
		tdata[i].y_end = (tdata[i].height / (double)NUM_THREADS) * (i + 1);
		tdata[i].y_scale_start = (scene->settings.disp_h
				/ (double)NUM_THREADS) * i;
		tdata[i].y_scale_end = (scene->settings.disp_h
				/ (double)NUM_THREADS) * (i + 1);
		i++;
	}
}

void	exec_thread(t_thread_data *tdata, void *func)
{
	pthread_t	threads[NUM_THREADS];
	int			i;

	i = -1;
	while (++i < NUM_THREADS)
		pthread_create(&threads[i], NULL, func, &tdata[i]);
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
}
