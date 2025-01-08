/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:23:48 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:23:49 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	mapping_right(double *x, double *y, t_vector *p)
{
	*x = (fmod(1 - p->z, 2.0) / 2.0);
	*y = (fmod(1 + p->y, 2.0) / 2.0);
}

void	mapping_left(double *x, double *y, t_vector *p)
{
	*x = (fmod(1 + p->z, 2.0) / 2.0);
	*y = (fmod(1 + p->y, 2.0) / 2.0);
}
