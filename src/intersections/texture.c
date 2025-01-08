/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:25:55 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:56:23 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vector	normal_at(const t_shape *shape, const t_vector *itx_point)
{
	t_vector	normal;
	t_vector	world_normal;

	if (shape->type == SPHERE)
		return (sphere_normal(&normal, shape, itx_point));
	else if (shape->type == PLANE)
		return (plane_normal(shape, itx_point));
	else if (shape->type == CYLINDER)
		return (cylinder_normal(shape, itx_point));
	else if (shape->type == CONE)
		return (cone_normal(shape, itx_point));
	normal = cube_normal(shape, itx_point);
	if (shape->normal_tex != NULL)
		return (normal_map(&normal, shape, itx_point));
	mat_vec_mult(&world_normal, &shape->norm_transf, &normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}

t_vector	get_texture_coords(const t_shape *shape, double u, double v,
				t_vector *normal)
{
	t_color		normal_coords;

	if (shape->tex_tile != 0)
	{
		u = (int)floor(u * (shape->text_height - 1) * shape->tex_tile) \
			% shape->text_height;
		v = (int)floor(v * (shape->tex_width - 1) * shape->tex_tile) \
			% shape->tex_width;
	}
	else
	{
		u = (int)floor(u * (shape->text_height - 1));
		v = (int)floor(v * (shape->tex_width - 1));
	}
	if (u >= shape->text_height || v >= shape->tex_width)
		return (*normal);
	normal_coords = shape->normal_tex[(int)u][(int)v];
	normal->w = 0;
	normal->x = 2 * normal_coords.r - 1;
	normal->y = 2 * normal_coords.g - 1;
	normal->z = 2 * normal_coords.b - 1;
	normalize_vector(normal);
	return (*normal);
}

void	ft_swapd(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
