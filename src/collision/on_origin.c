/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_origin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:06:23 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:59:58 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vector	triple_cross_product(t_vector *v1, t_vector *v2,
	const t_vector *v3)
{
	t_vector	v;
	t_vector	result;

	cross_product(&v, v1, v2);
	cross_product(&result, &v, v3);
	return (result);
}

bool	line_on_origin(t_simplex *simplex, t_vector *dir)
{
	t_vector	v1;
	t_vector	v2;

	sub_vector(&v1, &simplex->arr[1], &simplex->arr[0]);
	negate_vector(&v2, &simplex->arr[0]);
	if (dot_product(&v1, &v2) > 0)
		*dir = triple_cross_product(&v1, &v2, &v1);
	else
	{
		simplex->size = 1;
		*dir = v1;
	}
	normalize_vector(dir);
	return (false);
}
