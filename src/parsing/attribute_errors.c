/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:25:22 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:25:23 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	print_color_error(t_color_err *err, const char *line, int line_num,
			char *element)
{
	if (err->r)
		printf(RED_ERR);
	else if (err->g)
		printf(GREEN_ERR);
	else if (err->b)
		printf(BLUE_ERR);
	else if (err->other)
		printf(GENERIC_ERROR, element, line_num, line);
	return (ft_memchr(err, 1, sizeof(t_color_err)));
}

bool	print_orient_error(t_orient_err *err, const char *line, int line_num,
			char *element)
{
	if (err->x)
		printf(ORIENT_X_OOR);
	else if (err->y)
		printf(ORIENT_Y_OOR);
	else if (err->z)
		printf(ORIENT_Z_OOR);
	else if (err->zero)
		printf(ORIENT_ZERO);
	else if (err->other)
		printf(GENERIC_ERROR, element, line_num, line);
	return (ft_memchr(err, 1, sizeof(t_orient_err)));
}
