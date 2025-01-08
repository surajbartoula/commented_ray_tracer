/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:21:52 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 22:26:43 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	normalize_vector(t_vector *vect)
{
	scale_vector(vect, vect, 1 / vector_magnitude(vect));
	vect->w = 0;
}

double	vector_magnitude(const t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

double	dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}

void	cross_product(t_vector *result, const t_vector *v1, const t_vector *v2)
{
	result->x = v1->y * v2->z - v1->z * v2->y;
	result->y = v1->z * v2->x - v1->x * v2->z;
	result->z = v1->x * v2->y - v1->y * v2->x;
	result->w = 0;
}

double	vector_distance(const t_vector *v1, const t_vector *v2)
{
	t_vector	sub;

	sub_vector(&sub, v1, v2);
	return (vector_magnitude(&sub));
}
