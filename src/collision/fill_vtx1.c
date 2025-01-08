/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_vtx1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:59:24 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:59:41 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	fill_vtx0(t_vector *vtx)
{
	vtx[0].x = 1;
	vtx[0].y = 1;
	vtx[0].z = 1;
	vtx[0].w = 1;
}

void	fill_vtx1(t_vector *vtx)
{
	vtx[1].x = 1;
	vtx[1].y = 1;
	vtx[1].z = -1;
	vtx[1].w = 1;
}

void	fill_vtx2(t_vector *vtx)
{
	vtx[2].x = 1;
	vtx[2].y = -1;
	vtx[2].z = 1;
	vtx[2].w = 1;
}

void	fill_vtx3(t_vector *vtx)
{
	vtx[3].x = 1;
	vtx[3].y = -1;
	vtx[3].z = -1;
	vtx[3].w = 1;
}

void	fill_vtx4(t_vector *vtx)
{
	vtx[4].x = -1;
	vtx[4].y = 1;
	vtx[4].z = 1;
	vtx[4].w = 1;
}
