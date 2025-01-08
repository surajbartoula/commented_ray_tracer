/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:25:40 by allan             #+#    #+#             */
/*   Updated: 2025/01/06 23:20:12 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//parse light properties

void	parse_light_props(t_scene *scene, t_light *light, char **splitted)
{
	bool	success;
	double	col_sum;

	success = true;
	light->type = POINT;
	parse_color(&light->color, splitted[3], &scene->error_flag.light.color);
	if (mem_error(&scene->error_flag))
		return ;
	col_sum = light->color.r + light->color.g + light->color.b;
	if (light->color.r != 0 && light->color.g != 0 && light->color.b != 0)
	{
		light->color.r /= col_sum;
		light->color.g /= col_sum;
		light->color.b /= col_sum;
	}
	parse_coordinates(&light->position, splitted[1], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.light.coords = true;
	light->intensity = ft_atof(splitted[2], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.light.intensity_other = true;
	if (mem_error(&scene->error_flag) == false
		&& (light->intensity < 0.0 || light->intensity > 1.0))
		scene->error_flag.light.intensity_range = true;
	light->intensity *= 2;
}

void	parse_light(t_scene *scene, char **splitted)
{
	if (scene->count.lights == LIGHT_MAX)
	{
		scene->error_flag.light.max_lights = true;
		return ;
	}
	if (split_count(splitted) != 4)
	{
		scene->error_flag.light.other = true;
		return ;
	}
	//scene->lights pointing to 20 lights.
	if (scene->lights == NULL)
		scene->lights = ft_calloc(LIGHT_MAX, sizeof(t_light));
	if (scene->lights == NULL)
		return ;
	parse_light_props(scene, &scene->lights[scene->count.lights], splitted);
	identity_matrix(&scene->lights[scene->count.lights].added_rots);
	scene->count.lights++;
}

//Normalizes the ambient light's RGB color components and adjusts its intensity.
bool	parse_ambient_props(t_scene *scene)
{
	double	col_sum;

	col_sum = scene->ambient.color.r + scene->ambient.color.g \
	+ scene->ambient.color.b;
	if (col_sum != 0)
	{
		scene->ambient.color.r /= col_sum;
		scene->ambient.color.g /= col_sum;
		scene->ambient.color.b /= col_sum;
	}
	scene->count.ambience++;
	scene->ambient.intensity *= 2;
	return (true);
}
