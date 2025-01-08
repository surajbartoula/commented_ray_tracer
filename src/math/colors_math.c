/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:29:14 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/05 18:43:16 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	add_colors(t_color *res, const t_color *c1, const t_color *c2)
{
	res->r = c1->r + c2->r;
	res->g = c1->g + c2->g;
	res->b = c1->b + c2->b;
}

void	mult_color(t_color *res, const t_color *color, double val)
{
	res->r = color->r * val;
	res->g = color->g * val;
	res->b = color->b * val;
}

void	sub_colors(t_color *res, const t_color *c1, const t_color *c2)
{
	res->r = c1->r - c2->r;
	res->g = c1->g - c2->g;
	res->b = c1->b - c2->b;
}

void	blend_colors(t_color *res, const t_color *c1, const t_color *c2)
{
	res->r = c1->r * c2->r;
	res->g = c1->g * c2->g;
	res->b = c1->b * c2->b;
}

int	color_diff(int c1, int c2)
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
