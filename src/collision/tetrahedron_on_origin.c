/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrahedron_on_origin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:10:46 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 15:00:20 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	handle_sim_orientation(t_tetrahedron_data *data,
	t_simplex *simplex, t_vector *dir)
{
	t_vector	temp;

	if (dot_product(&data->abc, &data->ao) > 0)
	{
		simplex->size = 3;
		return (triangle_on_origin(simplex, dir));
	}
	if (dot_product(&data->acd, &data->ao) > 0)
	{
		simplex->size = 3;
		simplex->arr[1] = simplex->arr[2];
		simplex->arr[2] = simplex->arr[3];
		return (triangle_on_origin(simplex, dir));
	}
	if (dot_product(&data->adb, &data->ao) > 0)
	{
		simplex->size = 3;
		temp = simplex->arr[1];
		simplex->arr[1] = simplex->arr[3];
		simplex->arr[2] = temp;
		return (triangle_on_origin(simplex, dir));
	}
	return (true);
}

bool	tetrahedron_on_origin(t_simplex *simplex, t_vector *dir)
{
	t_tetrahedron_data	data;

	sub_vector(&data.ab, &simplex->arr[1], &simplex->arr[0]);
	sub_vector(&data.ac, &simplex->arr[2], &simplex->arr[0]);
	sub_vector(&data.ad, &simplex->arr[3], &simplex->arr[0]);
	negate_vector(&data.ao, &simplex->arr[0]);
	cross_product(&data.abc, &data.ab, &data.ac);
	cross_product(&data.acd, &data.ac, &data.ad);
	cross_product(&data.adb, &data.ad, &data.ab);
	if (handle_sim_orientation(&data, simplex, dir))
		return (true);
	return (true);
}
