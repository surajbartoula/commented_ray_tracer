/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:25:43 by allan             #+#    #+#             */
/*   Updated: 2025/01/06 16:54:07 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	parse_ambient(t_scene *scene, char **splitted)
{
	bool	status;

	status = true;
	if (split_count(splitted) != 3)
		return (scene->error_flag.ambient.other = true, false);
	scene->ambient.intensity = ft_atof(splitted[1], &status);
	if (status == false || scene->ambient.intensity < 0.0
		|| scene->ambient.intensity > 1.0)
	{
		if (status == true)
			scene->error_flag.ambient.intensity_range = true;
		else
			scene->error_flag.ambient.intensity_other = true;
		return (false);
	}
	parse_color(&scene->ambient.color, splitted[2],
		&scene->error_flag.ambient.color);
	if (mem_error(&scene->error_flag))
		return (false);
	return (parse_ambient_props(scene)); //parse ambient properties.
}

void	parse_camera(t_scene *scene, char **split)
{
	bool	status;

	status = true;
	if (split_count(split) != 4)
	{
		scene->error_flag.cam.other = true;
		return ;
	}
	parse_coordinates(&scene->cam.pos, split[1], &status);
	if (mem_error(&scene->error_flag) == false && status == false)
		scene->error_flag.cam.coord = true;
	parse_orientation(&scene->cam.dir, split[2], &scene->error_flag.cam.dir);
	if (mem_error(&scene->error_flag))
		return ;
	//cam.dir.x and cam.dir.z has less than 0.01 comparision but cam.dir.y has greater than 0.1 comparision to make sure the camera is not facing to sky.
	if (!mem_error(&scene->error_flag) && fabs(scene->cam.dir.x) < 0.01
		&& fabs(scene->cam.dir.y) > 0.01 && fabs(scene->cam.dir.z) < 0.01)
		scene->error_flag.cam.up_vector = true;
	scene->cam.fov = ft_atof(split[3], &status);
	if (!mem_error(&scene->error_flag)
		&& (!status || !is_num(split[3], true)))
		scene->error_flag.cam.fov_other = true;
	if (mem_error(&scene->error_flag) == false
		&& (scene->cam.fov < 1 || scene->cam.fov > 180))
		scene->error_flag.cam.fov_range = true;
	scene->count.cameras++;
}
