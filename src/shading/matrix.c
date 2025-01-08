/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:23:53 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:23:54 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	initialize_matrix(t_mat4 *mat, double x, double y, double z)
{
	ft_bzero(mat, sizeof(t_mat4));
	(*mat)[0][0] = x;
	(*mat)[1][1] = y;
	(*mat)[2][2] = z;
	(*mat)[3][3] = 1;
}

void	mat4_multiply(t_vector *res, const t_mat4 *mat,
	const t_vector *vec)
{
	res->x = vec->x * (*mat)[0][0] + vec->y * (*mat)[0][1] \
		+ vec->z * (*mat)[0][2] + vec->w * (*mat)[0][3];
	res->y = vec->x * (*mat)[1][0] + vec->y * (*mat)[1][1] \
		+ vec->z * (*mat)[1][2] + vec->w * (*mat)[1][3];
	res->z = vec->x * (*mat)[2][0] + vec->y * (*mat)[2][1] \
		+ vec->z * (*mat)[2][2] + vec->w * (*mat)[2][3];
	res->w = vec->x * (*mat)[3][0] + vec->y * (*mat)[3][1] \
		+ vec->z * (*mat)[3][2] + vec->w * (*mat)[3][3];
}
