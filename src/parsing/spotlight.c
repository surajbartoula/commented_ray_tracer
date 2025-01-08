/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:38 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:39 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	parse_spotlight_props2(t_light *light, char **splitted, t_scene *scene)
{
	bool	success;
	double	col_sum;

	success = true;
	light->theta = ft_atof(splitted[4], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.light.angle_other = true;
	if (mem_error(&scene->error_flag) == false
		&& (light->theta < 0.0 || light->theta > 180))
		scene->error_flag.light.angle_range = true;
	light->theta *= DEG_TO_RAD;
	parse_color(&light->color, splitted[5], &scene->error_flag.light.color);
	if (mem_error(&scene->error_flag))
		return ;
	col_sum = light->color.r + light->color.g + light->color.b;
	if (light->color.r != 0 && light->color.g != 0 && light->color.b != 0)
	{
		light->color.r /= col_sum;
		light->color.g /= col_sum;
		light->color.b /= col_sum;
	}
}

void	parse_spotlight_props(t_scene *scene, t_light *light, char **splitted)
{
	bool	success;

	success = true;
	light->type = SPOT;
	parse_coordinates(&light->position, splitted[1], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.light.coords = true;
	light->intensity = ft_atof(splitted[2], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.light.intensity_other = true;
	if (mem_error(&scene->error_flag) == false
		&& (light->intensity < 0.0 || light->intensity > 1.0))
		scene->error_flag.light.intensity_range = true;
	light->intensity *= 1.8;
	parse_orientation(&light->init_direction, splitted[3],
		&scene->error_flag.light.orient);
	if (mem_error(&scene->error_flag))
		return ;
	parse_spotlight_props2(light, splitted, scene);
}

void	parse_spotlight(t_scene *scene, char **splitted)
{
	if (scene->count.lights == LIGHT_MAX)
	{
		scene->error_flag.light.max_lights = true;
		return ;
	}
	if (split_count(splitted) != 6)
	{
		scene->error_flag.light.other = true;
		return ;
	}
	if (scene->lights == NULL)
		scene->lights = ft_calloc(LIGHT_MAX, sizeof(t_light));
	if (scene->lights == NULL)
		return ;
	parse_spotlight_props(scene, &scene->lights[scene->count.lights], splitted);
	identity_matrix(&scene->lights[scene->count.lights].added_rots);
	scene->count.lights++;
}
