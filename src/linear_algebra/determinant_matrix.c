/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:38:43 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/27 18:52:38 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathRT.h"

static double	cofactor3(const t_mat3 *mat3, int row, int col)
{
	t_mat2	mat2;

	submat3(&mat2, mat3, row, col);
	if ((row + col) % 2 == 1)
		return (det2(&mat2));
	return (-det2(&mat2));
}

void	submat4(t_mat3 *res, const t_mat4 *mat, int row, int col)
{
	int	i;
	int	j;
	int	i_sub;
	int	j_sub;

	i = -1;
	i_sub = 0;
	while (++i < 4)
	{
		if (i == row)
			continue ;
		j_sub = 0;
		j = 0;
		while (j < 4)
		{
			if (j == col)
				j++;
			else
				(*res)[i_sub][j_sub++] = (*mat)[i][j++];
		}
		i_sub++;
	}
}

double	det3(const t_mat3 *mat3)
{
	return (cofactor3(mat3, 0, 0) * (*mat3)[0][0]
			+ cofactor3(mat3, 0, 1) * (*mat3)[0][1]
			+ cofactor3(mat3, 0, 2) * (*mat3)[0][2]);
}

double	cofactor4(const t_mat4 *mat4, int row, int col)
{
	t_mat3	mat3;

	submat4(&mat3, mat4, row, col);
	if ((row + col) % 2 == 1)
		return (det3(&mat3));
	return (-det3(&mat3));
}

double	det4(const t_mat4 *matrix)
{
	return (cofactor4(matrix, 0, 0) * (*matrix)[0][0]
			+ cofactor4(matrix, 0, 1) * (*matrix)[0][1]
			+ cofactor4(matrix, 0, 2) * (*matrix)[0][2]
			+ cofactor4(matrix, 0, 3) * (*matrix)[0][3]);
}
