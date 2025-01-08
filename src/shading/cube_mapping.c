/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:23:39 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:23:40 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	mapping_up(double *x, double *y, t_vector *p)
{
	*x = (fmod(1 - p->x, 2.0) / 2.0);
	*y = (fmod(1 - p->z, 2.0) / 2.0);
}

void	mapping_down(double *x, double *y, t_vector *p)
{
	*x = (fmod(1 - p->x, 2.0) / 2.0);
	*y = (fmod(1 + p->z, 2.0) / 2.0);
}

void	mapping_front(double *x, double *y, t_vector *p)
{
	*x = (fmod(1 + p->x, 2.0) / 2.0);
	*y = (fmod(1 + p->y, 2.0) / 2.0);
}

void	mapping_back(double *x, double *y, t_vector *p)
{
	*x = (fmod(1 - p->x, 2.0) / 2.0);
	*y = (fmod(1 + p->y, 2.0) / 2.0);
}

void	cubicle_mapping(double *x, double*y, t_vector *p)
{
	double	abs_x;
	double	abs_y;
	double	abs_z;
	double	cord;

	abs_y = 0.0;
	abs_z = 0.0;
	abs_x = fabs(p->x);
	abs_x = fabs(p->x);
	abs_x = fabs(p->x);
	cord = max_with_three(abs_x, abs_y, abs_z);
	if (cord == p->x)
		mapping_right(x, y, p);
	else if (cord == -p->x)
		mapping_left(x, y, p);
	else if (cord == p->y)
		mapping_up(x, y, p);
	else if (cord == -p->y)
		mapping_down(x, y, p);
	else if (cord == p->z)
		mapping_front(x, y, p);
	else if (cord == -p->y)
		mapping_back(x, y, p);
}
