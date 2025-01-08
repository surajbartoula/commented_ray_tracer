/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:25:59 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:00 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	print_error(t_scene *scene, const char *line, int line_num,
			const char *identifer)
{
	t_error_flags	*flags;

	flags = &scene->error_flag;
	if (flags->settings_err)
		return ;
	if (flags->unknown_identifier == true)
	{
		printf(UNKNOWN_IDENTIFIER, identifer, line_num, line);
		return ;
	}
	if (print_ambient_light_error(&flags->ambient, line, line_num))
		return ;
	if (print_cam_error(&flags->cam, line, line_num))
		return ;
	if (print_light_error(&flags->light, line, line_num))
		return ;
	if (flags->shape.max_shapes)
	{
		printf(MAX_ELEMENT_ERROR, SHAPE_MAX, "shapes");
		return ;
	}
	print_shape_error(&scene->shapes[scene->count.shapes],
		&scene->error_flag.shape, line, line_num);
}

bool	mem_error(t_error_flags *err)
{
	return (ft_memchr(err, 1, sizeof(t_error_flags)));
}

void	invalid_argument(void)
{
	ft_putendl_fd("Please provide the correct arguments", 2);
}

void	wrong_file_format(void)
{
	ft_putendl_fd("Provide .rt file format", 2);
}

void	opening_file_failed(char *file_name)
{
	ft_putendl_fd("Opening file failed", 2);
	printf("%s", file_name);
	perror(NULL);
}
