/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:14:29 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/08 15:21:59 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//blend colors with mix
int	mix_color(int c1, int c2, double mix)
{
	int				r;
	int				g;
	int				b;
	unsigned char	*col1;
	unsigned char	*col2;

	col1 = (unsigned char *)&c1;
	col2 = (unsigned char *)&c2;
	r = col1[2] * mix + col2[2] * (1 - mix);
	g = col1[1] * mix + col2[1] * (1 - mix);
	b = col1[0] * mix + col2[0] * (1 - mix);
	return (r << 16 | g << 8 | b);
}

int	color_difference(int c1, int c2)
{
	int				r_diff;
	int				g_diff;
	int				b_diff;
	unsigned char	*col1;
	unsigned char	*col2;

	col1 = (unsigned char *)&c1;
	col2 = (unsigned char *)&c2;
	r_diff = abs(col1[2] - col2[2]);
	g_diff = abs(col1[1] - col2[1]);
	b_diff = abs(col1[0] - col2[0]);
	return (r_diff + g_diff + b_diff);
}

static unsigned int	clamp_color(double color)
{
	color *= 255;
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

unsigned int	create_mlx_color(t_color *color)
{
	return (clamp_color(color->a) << 24 | clamp_color(color->r) << 16
		| clamp_color(color->g) << 8 | clamp_color(color->b));
}

//convert hex color to t_color with value between 0-1 that's why divide by 255
t_color	int_to_color(int hex_color)
{
	t_color	color;

	color.a = 0;
	color.r = ((unsigned char *)&hex_color)[2] / 255.0f;
	color.g = ((unsigned char *)&hex_color)[1] / 255.0f;
	color.b = ((unsigned char *)&hex_color)[0] / 255.0f;
	return (color);
}vbdf
