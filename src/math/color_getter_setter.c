/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_getter_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:34:30 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/28 11:49:36 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	set_color(t_thread_data *tdata, int x, int y, int color)
{
	int	bpp;

	if (x >= tdata->width || y > tdata->height || x < 0 || y < 0)
		return ;
	bpp = tdata->scene->disp->bpp;
	*(int *)(tdata->addr + ((y * tdata->width) + x) * bpp) = color;
}

int	get_color(t_thread_data *tdata, int x, int y)
{
	int	bpp;

	bpp = tdata->scene->disp->bpp;
	return (*(int *)(tdata->addr + ((y * tdata->width) + x) * bpp));
}
