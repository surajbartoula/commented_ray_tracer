/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modification2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:23:59 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:24:00 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_color	shade_point(t_intersections *arr, t_scene *scene, t_ray *ray)
{
	t_intersection	*itx;
	int				light_idx;
	t_color			final_color;
	t_color			surface_color;
	t_color			reflected;

	itx = hit(arr);
	ft_bzero(&final_color, sizeof(t_color));
	if (itx != NULL)
	{
		prepare_computations(itx, ray);
		light_idx = 0;
		while (light_idx < scene->count.lights)
		{
			surface_color = glear(itx, scene, light_idx);
			reflected = cast_reflection_ray(scene, itx,
					scene->settings.reflection_depth, light_idx);
			add_colors(&final_color, &final_color, &surface_color);
			add_colors(&final_color, &final_color, &reflected);
			light_idx++;
		}
	}
	return (final_color);
}

bool	check_spotlight(t_scene *scene, int light_idx, t_ray *ray,
			double *angle)
{
	if (scene->lights[light_idx].type == SPOT)
	{
		*angle = (dot_product(&ray->dir, &scene->lights[light_idx].direction));
		if (*angle < 0)
			return (true);
		if (*angle >= -1 && *angle <= 1)
		{
			*angle = acos(*angle);
			if (*angle > (scene->lights[light_idx].theta / 4))
				return (true);
		}
	}
	return (false);
}

void	glear_diffusion(t_color *result, t_glear *glear)
{
	result->r += glear->diffuse.r + glear->specular.r;
	result->g += glear->diffuse.g + glear->specular.g;
	result->b += glear->diffuse.b + glear->specular.b;
}
