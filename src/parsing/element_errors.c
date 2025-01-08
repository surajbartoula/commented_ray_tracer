/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:25:35 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:25:36 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	print_ambient_light_error(t_ambient_err *err, const char *line,
			int line_num)
{
	if (err->intensity_other)
	{
		printf(GENERIC_ERROR, "ambient light intensity", line_num, line);
		printf(AMBIENT_LIGHT_SYNTAX);
	}
	else if (err->intensity_range)
		printf(LIGHT_INTENSITY_OOR, "Ambient light", line_num, line);
	else if (print_color_error(&err->color, line, line_num,
			"ambient light color"))
		return (true);
	else if (err->other)
	{
		printf(GENERIC_ERROR, "ambient light", line_num, line);
		printf(AMBIENT_LIGHT_SYNTAX);
	}
	return (ft_memchr(err, 1, sizeof(t_ambient_err)));
}

bool	print_cam_error(t_cam_err *err, const char *line, int line_num)
{
	if (err->coord)
		printf(GENERIC_ERROR, "camera origin", line_num, line);
	else if (print_orient_error(&err->dir, line, line_num,
			"camera orientation") && err->dir.other)
		printf(CAMERA_SYNTAX);
	else if (err->up_vector)
	{
		printf(GENERIC_ERROR, "camera orientation", line_num, line);
		printf(CAMERA_UP_VECTOR);
	}
	else if (err->fov_range || err->fov_other)
	{
		printf(GENERIC_ERROR, "camera field of view", line_num, line);
		if (err->fov_range)
			printf(CAMERA_FOV_OOR);
	}
	else if (err->other)
		printf(GENERIC_ERROR, "camera", line_num, line);
	if (err->coord || err->fov_other || err->other)
		printf(CAMERA_SYNTAX);
	return (ft_memchr(err, 1, sizeof(t_cam_err)));
}

bool	print_light_error(t_light_errors *err, const char *line, int line_num)
{
	if (err->coords)
		printf(GENERIC_ERROR, "light position", line_num, line);
	else if (err->intensity_range)
		printf(LIGHT_INTENSITY_OOR, "light", line_num, line);
	else if (err->intensity_other)
		printf(GENERIC_ERROR, "light intensity", line_num, line);
	else if (err->max_lights)
		printf(MAX_ELEMENT_ERROR, LIGHT_MAX, "lights");
	else if (err->other)
		printf(GENERIC_ERROR, "light", line_num, line);
	else if (print_color_error(&err->color, line, line_num,
			"light color") && err->other)
		printf(LIGHT_SYNTAX);
	else if (print_orient_error(&err->orient, line, line_num,
			"spotlight orientation") && err->orient.other == true)
		printf(SPOTLIGHT_SYNTAX);
	else if (err->angle_other)
		printf(GENERIC_ERROR""SPOTLIGHT_SYNTAX, "spotlight beam width",
			line_num, line);
	else if (err->angle_range)
		printf(SPOTLIGHT_ANGLE_OOR, line_num, line);
	if (err->coords || err->intensity_other || err->other)
		printf(LIGHT_SYNTAX);
	return (ft_memchr(err, 1, sizeof(t_light_errors)));
}
