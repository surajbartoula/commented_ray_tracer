/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:52:38 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:53:59 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	draw_shape_type(t_scene *scene, t_shape *shape, t_vector *proj_origin)
{
	if (shape->type == SPHERE)
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			(proj_origin->x * scene->settings.disp_w),
			(proj_origin->y - 0.12) * scene->settings.disp_h,
			0xffffff, "Sphere");
	if (shape->type == CYLINDER)
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			(proj_origin->x * scene->settings.disp_w),
			(proj_origin->y - 0.12) * scene->settings.disp_h,
			0xffffff, "Cylinder");
	if (shape->type == CUBE)
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			(proj_origin->x * scene->settings.disp_w),
			(proj_origin->y - 0.12) * scene->settings.disp_h,
			0xffffff, "Cube");
	if (shape->type == CONE)
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			(proj_origin->x * scene->settings.disp_w),
			(proj_origin->y - 0.12) * scene->settings.disp_h,
			0xffffff, "Cone");
}

void	draw_shape_coordinates(t_shape *shape, t_scene *scene,
			t_vector *proj_origin)
{
	char	*str;

	str = ftoa(shape->origin.x);
	str = ft_strjoin_free(" x: ", str, 2);
	mlx_string_put(scene->disp->mlx, scene->disp->win,
		(proj_origin->x * scene->settings.disp_w),
		(proj_origin->y - 0.10) * scene->settings.disp_h,
		0xffffff, str);
	free(str);
	str = ftoa(shape->origin.y);
	str = ft_strjoin_free(" y: ", str, 2);
	mlx_string_put(scene->disp->mlx, scene->disp->win,
		(proj_origin->x * scene->settings.disp_w),
		(proj_origin->y - 0.08) * scene->settings.disp_h,
		0xffffff, str);
	free(str);
	str = ftoa(shape->origin.z);
	str = ft_strjoin_free(" z: ", str, 2);
	mlx_string_put(scene->disp->mlx, scene->disp->win,
		(proj_origin->x * scene->settings.disp_w),
		(proj_origin->y - 0.06) * scene->settings.disp_h,
		0xffffff, str);
	free(str);
}

void	draw_shape_properties(t_shape *shape, t_scene *scene,
			t_vector *proj_origin)
{
	char	*str;

	if (shape->type == SPHERE || shape->type == CONE || shape->type == CYLINDER)
	{
		str = ftoa(shape->props.radius);
		str = ft_strjoin_free(" radius: ", str, 2);
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			(proj_origin->x * scene->settings.disp_w),
			(proj_origin->y - 0.04) * scene->settings.disp_h,
			0xffffff, str);
		free(str);
	}
	if (shape->type == CYLINDER || shape->type == CONE)
	{
		str = ftoa(shape->props.height);
		str = ft_strjoin_free(" height: ", str, 2);
		mlx_string_put(scene->disp->mlx, scene->disp->win,
			(proj_origin->x * scene->settings.disp_w),
			(proj_origin->y - 0.02) * scene->settings.disp_h,
			0xffffff, str);
		free(str);
	}
}

t_vector	get_origin(t_shape *shape, t_scene *scene)
{
	t_vector	origin;
	t_vector	orient;
	t_vector	proj_origin;

	origin = shape->origin;
	origin.x -= 0.2;
	if (shape->type == SPHERE || shape->type == CYLINDER)
		origin.y += shape->props.radius;
	if (shape->type == CONE)
		origin.y += shape->props.height / 2;
	if (shape->type == CUBE)
	{
		mat_vec_mult(&orient, &shape->added_rots, &shape->orientation);
		origin.y += shape->props.scale.y * fabs(orient.y) + shape->props.scale.x
			* fabs(orient.x) + shape->props.scale.z * fabs(orient.z);
	}
	mat_vec_mult(&proj_origin, &scene->cam.transform, &origin);
	return (proj_origin);
}
