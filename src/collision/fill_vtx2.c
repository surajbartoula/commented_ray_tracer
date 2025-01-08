/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_vtx2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:00:28 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/02 23:57:45 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	fill_vtx5(t_vector *vtx)
{
	vtx[5].x = -1;
	vtx[5].y = -1;
	vtx[5].z = 1;
	vtx[5].w = 1;
}

void	fill_vtx6(t_vector *vtx)
{
	vtx[6].x = -1;
	vtx[6].y = -1;
	vtx[6].z = -1;
	vtx[6].w = 1;
}

void	fill_vtx7(t_vector *vtx)
{
	vtx[7].x = -1;
	vtx[7].y = 1;
	vtx[7].z = -1;
	vtx[7].w = 1;
}
