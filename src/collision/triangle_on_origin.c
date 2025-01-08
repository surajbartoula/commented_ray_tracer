/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_on_origin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:02:17 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 15:46:28 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	check_triangle_orientation(t_simplex *simplex, t_vector *dir,
	t_triangledata *tdata)
{
	cross_product(&tdata->pbc_pc, &tdata->pbc, &tdata->pc);
	if (dot_product(&tdata->pbc_pc, &tdata->po) > 0)
	{
		if (dot_product(&tdata->pc, &tdata->po) > 0)
		{
			simplex->size = 2;
			simplex->arr[1] = simplex->arr[2];
			*dir = triple_cross_product(&tdata->pc, &tdata->po, &tdata->pc);
		}
		else
		{
			simplex->size = 2;
			return (true);
		}
	}
	return (false);
}

bool	handle_line_interaction(t_simplex *simplex, t_vector *dir,
	t_triangledata *data)
{
	t_vector	temp;

	cross_product(&data->pb_pbc, &data->pb, &data->pbc);
	if (dot_product(&data->pb_pbc, &data->po) > 0)
	{
		simplex->size = 2;
		return (true);
	}
	else
	{
		if (dot_product(&data->pbc, &data->po) > 0)
			*dir = data->pbc;
		else
		{
			temp = simplex->arr[1];
			simplex->arr[1] = simplex->arr[2];
			simplex->arr[2] = temp;
			simplex->size = 3;
			*dir = data->pbc;
			negate_vector(dir, &data->pbc);
		}
	}
	return (false);
}

bool	triangle_on_origin(t_simplex *simplex, t_vector *dir)
{
	t_triangledata	tdata;

	sub_vector(&tdata.pb, &simplex->arr[1], &simplex->arr[0]);
	sub_vector(&tdata.pc, &simplex->arr[2], &simplex->arr[0]);
	negate_vector(&tdata.po, &simplex->arr[0]);
	cross_product(&tdata.pbc, &tdata.pb, &tdata.pc);
	if (check_triangle_orientation(simplex, dir, &tdata))
		return (line_on_origin(simplex, dir));
	return (handle_line_interaction(simplex, dir, &tdata));
}
