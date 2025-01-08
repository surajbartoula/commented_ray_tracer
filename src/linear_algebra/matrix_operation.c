/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:43:37 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 01:51:23 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	matrix_multiply(t_mat4 *result, const t_mat4 *m1, const t_mat4 *m2)
{
	int			row;
	t_mat4		temp;

	row = 0;
	while (row < 4)
	{
		temp[row][0] = (*m1)[row][0] * (*m2)[0][0]
			+ (*m1)[row][1] * (*m2)[1][0]
			+ (*m1)[row][2] * (*m2)[2][0]
			+ (*m1)[row][3] * (*m2)[3][0];
		temp[row][1] = (*m1)[row][0] * (*m2)[0][1]
			+ (*m1)[row][1] * (*m2)[1][1]
			+ (*m1)[row][2] * (*m2)[2][1]
			+ (*m1)[row][3] * (*m2)[3][1];
		temp[row][2] = (*m1)[row][0] * (*m2)[0][2]
			+ (*m1)[row][1] * (*m2)[1][2]
			+ (*m1)[row][2] * (*m2)[2][2]
			+ (*m1)[row][3] * (*m2)[3][2];
		temp[row][3] = (*m1)[row][0] * (*m2)[0][3]
			+ (*m1)[row][1] * (*m2)[1][3]
			+ (*m1)[row][2] * (*m2)[2][3]
			+ (*m1)[row][3] * (*m2)[3][3];
		row++;
	}
	ft_memcpy(result, &temp, sizeof(t_mat4));
}

void	mat_vec_mult(t_vector *result, const t_mat4 *mat,
			const t_vector *vec)
{
	result->x = vec->x * (*mat)[0][0] + vec->y * (*mat)[0][1]
		+ vec->z * (*mat)[0][2] + vec->w * (*mat)[0][3];
	result->y = vec->x * (*mat)[1][0] + vec->y * (*mat)[1][1]
		+ vec->z * (*mat)[1][2] + vec->w * (*mat)[1][3];
	result->z = vec->x * (*mat)[2][0] + vec->y * (*mat)[2][1]
		+ vec->z * (*mat)[2][2] + vec->w * (*mat)[2][3];
	result->w = vec->x * (*mat)[3][0] + vec->y * (*mat)[3][1]
		+ vec->z * (*mat)[3][2] + vec->w * (*mat)[3][3];
}

void	identity_matrix(t_mat4 *mat)
{
	ft_bzero(mat, sizeof(t_mat4));
	(*mat)[0][0] = 1;
	(*mat)[1][1] = 1;
	(*mat)[2][2] = 1;
	(*mat)[3][3] = 1;
}

void	tanspose_matrix(t_mat4 *mat)
{
	double	temp;
	int		row;
	int		col;

	row = 1;
	while (row < 4)
	{
		col = 0;
		while (col < row)
		{
			temp = (*mat)[row][col];
			(*mat)[row][col] = (*mat)[col][row];
			(*mat)[col][row] = temp;
			col++;
		}
		row++;
	}
}

void	axis_angle(t_mat4 *rot_mat, const t_vector *ax, double angle)
{
	(*rot_mat)[0][0] = cos(angle) + ax->x * ax->x * (1 - cos(angle));
	(*rot_mat)[0][1] = ax->x * ax->y * (1 - cos(angle)) - ax->z * sin(angle);
	(*rot_mat)[0][2] = ax->x * ax->z * (1 - cos(angle)) + ax->y * sin(angle);
	(*rot_mat)[0][3] = 0;
	(*rot_mat)[1][0] = ax->x * ax->y * (1 - cos(angle)) + ax->z * sin(angle);
	(*rot_mat)[1][1] = cos(angle) + ax->y * ax->y * (1 - cos(angle));
	(*rot_mat)[1][2] = ax->y * ax->z * (1 - cos(angle)) - ax->x * sin(angle);
	(*rot_mat)[1][3] = 0;
	(*rot_mat)[2][0] = ax->z * ax->x * (1 - cos(angle)) - ax->y * sin(angle);
	(*rot_mat)[2][1] = ax->z * ax->y * (1 - cos(angle)) + ax->x * sin(angle);
	(*rot_mat)[2][2] = cos(angle) + ax->z * ax->z * (1 - cos(angle));
	(*rot_mat)[2][3] = 0;
	(*rot_mat)[3][0] = 0;
	(*rot_mat)[3][1] = 0;
	(*rot_mat)[3][2] = 0;
	(*rot_mat)[3][3] = 1;
}
