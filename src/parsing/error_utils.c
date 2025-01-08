/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:25:55 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:25:56 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	print_shape_error(t_shape *shape, t_shape_errors *error,
			const char *line, int line_num)
{
	if (shape->type == SPHERE)
		return (print_sphere_error(error, line, line_num));
	if (shape->type == CUBE)
		return (print_cube_error(error, line, line_num));
	if (shape->type == PLANE)
		return (print_plane_error(error, line, line_num));
	if (shape->type == CYLINDER)
		return (print_cylinder_error(error, line, line_num));
	return (print_cone_error(error, line, line_num));
}

void	free_and_update1(char **rgb, t_color *color, t_color_err *errs)
{
	free_2d_array(rgb);
	check_color_range(color, errs);
}

void	free_and_update2(t_vector *position, double *res, char	**coords)
{
	position->x = res[0];
	position->y = res[1];
	position->z = res[2];
	position->w = 1;
	free_2d_array(coords);
}
