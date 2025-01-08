/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:54:56 by sbartoul          #+#    #+#             */
/*   Updated: 2024/11/28 11:22:00 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathRT.h"

void	inverse_matrix(t_mat4 *result, const t_mat4 *matrix)
{
	double	determinant;
	int		row;

	determinant = det4(matrix);
	if (fabs(determinant) < EPSILON)
		return ;
	row = 0;
	while (row < 4)
	{
		(*result)[0][row] = cofactor4(matrix, row, 0) / determinant;
		(*result)[1][row] = cofactor4(matrix, row, 1) / determinant;
		(*result)[2][row] = cofactor4(matrix, row, 2) / determinant;
		(*result)[3][row] = cofactor4(matrix, row, 3) / determinant;
		row++;
	}
}
