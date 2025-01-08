/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:59:55 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/04 11:24:53 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	cylindrical_map(double *u, double *v, t_vector *point)
{
	double	theta;

	theta = atan2(point->x, point->z);
	*u = 1 - (theta / (2 * M_PI) + 0.5);
	*v = point->y - floor(point->y);
}

t_color	texture_mapping(t_intersection *p, double h, double w)
{
	if (p->shape->tex_tile != 0)
	{
		h = (int)floor(h * ((p->shape->text_height - 1)
					* (p->shape->tex_tile))) % (p->shape->text_height);
		w = (int)floor(w * ((p->shape->tex_width - 1)
					* (p->shape->tex_tile))) % (p->shape->tex_width);
	}
	else
	{
		h = (int)floor(p->shape->text_height - 1);
		w = (int)floor(p->shape->tex_width - 1);
	}
	if (h >= p->shape->text_height || w >= p->shape->tex_width)
		return (p->shape->props.color);
	return (p->shape->diffuse_tex[(int)h][(int)w]);
}

t_color	get_texture_color(t_intersection *itx)
{
	t_vector	shape_point;
	double		u;
	double		v;

	mat4_multiply(&shape_point, &itx->shape->inv_transf, &itx->point);
	if (itx->shape->type == CYLINDER || itx->shape->type == CONE)
	{
		shape_point.y /= itx->shape->props.height;
		shape_point.y -= 0.5;
		cylindrical_map(&u, &v, &shape_point);
	}
	else if (itx->shape->type == SPHERE)
		spherical_map(&u, &v, &shape_point);
	else
		cubicle_mapping(&u, &v, &shape_point);
	if (u < 0 || v < 0)
		return (itx->shape->props.color);
	return (texture_mapping(itx, u, v));
}

t_color	get_shape_color(t_intersection *itx)
{
	if (itx->shape->diffuse_tex != NULL)
		return (get_texture_color(itx));
	if (itx->shape->props.pattern_type == NONE)
		return (itx->shape->props.color);
	if (itx->shape->props.pattern_type == STRIPE)
		return (stripe_pattern(itx, itx->over_point, coloring(0xffffff),
				coloring(0xff0000)));
	if (itx->shape->props.pattern_type == CHECKER_BOARD)
		return (checker_pattern(itx, &itx->over_point));
	if (itx->shape->props.pattern_type == GRADIENT)
		return (gradient_pattern(itx, itx->over_point, coloring(0xff0000),
				coloring(0x0000ff)));
	if (itx->shape->props.pattern_type == RING)
		return (ring_pattern(itx, itx->over_point, coloring(0xff0000),
				coloring(0x0000ff)));
	return (itx->shape->props.color);
}

bool	get_specular_and_diffuse(t_scene *scene, int light_idx,
	t_intersection *itx, t_glear *phong)
{
	double		light_dot_normal;
	t_vector	light_v;
	t_vector	reflect_v;
	double		spotlight_angle;

	spotlight_angle = 0;
	sub_vector(&light_v, &scene->lights[light_idx].position, &itx->over_point);
	normalize_vector(&light_v);
	itx->normal.w = 0;
	light_dot_normal = dot_product(&light_v, &itx->normal);
	if (light_dot_normal < 0 || is_shadow(scene, light_idx, &itx->over_point,
			&spotlight_angle))
		return (false);
	mult_color(&phong->diffuse, &phong->effective_color, light_dot_normal
		* itx->shape->props.diffuse * scene->lights[light_idx].intensity);
	if (scene->lights[light_idx].type == SPOT
		&& acos(spotlight_angle) > scene->lights[light_idx].theta * 0.9 / 4)
		mult_color(&phong->diffuse, &phong->diffuse, 0.8);
	negate_vector(&light_v, &light_v);
	reflect_vector(&reflect_v, &light_v, &itx->normal);
	calculate_specular(&reflect_v, itx, phong, &scene->lights[light_idx]);
	return (true);
}
