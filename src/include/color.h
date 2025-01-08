/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:07:10 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/02 20:12:35 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "miniRT.h"
# include "shape.h"

typedef struct s_shape	t_shape;

typedef struct s_color	t_color;
struct s_color
{
	double	r;
	double	g;
	double	b;
	double	a;
};

typedef struct s_glear	t_glear;
struct s_glear
{
	t_color		effective_color;
	t_color		diffuse;
	t_color		specular;
	t_color		ambient;
};

void			free_texture(t_shape *shape, t_color **color);
t_color			coloring(int hex_color);
void			blend_colors(t_color *res, const t_color *c1,
					const t_color *c2);
void			mult_color(t_color *res, const t_color *color, double pres);
void			add_colors(t_color *res, const t_color *c1, const t_color *c2);
void			glear_diffusion(t_color *result, t_glear *glear);
int				mix_color(int c1, int c2, double mix);
int				color_difference(int c1, int c2);
unsigned int	create_mlx_color(t_color *color);
t_color			int_to_color(int hex_color);

#endif