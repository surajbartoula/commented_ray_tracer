/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detmat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:52:20 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/27 18:53:05 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathRT.h"

double	det2(const t_mat2 *mat)
{
	return ((*mat)[0][0] * (*mat)[1][1] - (*mat)[0][1] * (*mat)[1][0]);
}

void	submat3(t_mat2 *res, const t_mat3 *mat, int row, int col)
{
	int	i;
	int	j;
	int	i_sub;
	int	j_sub;

	i = -1;
	i_sub = 0;
	while (++i < 3)
	{
		if (i == row)
			continue ;
		j_sub = 0;
		j = 0;
		while (j < 3)
		{
			if (j == col)
				j++;
			else
				(*res)[i_sub][j_sub++] = (*mat)[i][j++];
		}
		i_sub++;
	}
}
