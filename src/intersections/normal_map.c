/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:30:58 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/27 18:08:06 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vector	normal_from_texture(const t_shape *shape, const t_vector *itx_point)
{
	t_vector	shape_point;
	double		u;
	double		v;
	t_vector	normal;

	ft_bzero(&normal, sizeof(t_vector));
	normal.y = 1;
	mat_vec_mult(&shape_point, &shape->inv_transf, itx_point);
	if (shape->type == SPHERE)
		spherical_map(&u, &v, &shape_point);
	else if (shape->type == CYLINDER || shape->type == CONE)
	{
		shape_point.y /= shape->props.height;
		shape_point.y -= 0.5;
		cylindrical_map(&u, &v, &shape_point);
	}
	else
		cubicle_mapping(&u, &v, &shape_point);
	if (u < 0 || v < 0)
		return (normal);
	return (get_texture_coords(shape, u, v, &normal));
}

void	get_tb(t_vector *normal, t_vector *tb)
{
	t_vector	up;
	t_vector	z_up;

	ft_bzero(&up, sizeof(t_vector));
	ft_bzero(&z_up, sizeof(t_vector));
	up.y = 1;
	z_up.z = 1;
	cross_product(&tb[0], normal, &up);
	if (vector_magnitude(&tb[0]) < 0.000001)
		cross_product(&tb[0], normal, &z_up);
	normalize_vector(&tb[0]);
	cross_product(&tb[1], normal, &tb[0]);
	normalize_vector(&tb[1]);
}

t_vector	normal_map(t_vector *normal, const t_shape *shape,
				const t_vector *itx_point)
{
	t_vector		tb[2];
	t_vector		tex_normal;
	t_mat4			tbn;
	t_vector		final_normal;
	t_vector		world_normal;

	tex_normal = normal_from_texture(shape, itx_point);
	get_tb(normal, tb);
	ft_bzero(&tbn, sizeof(t_mat4));
	tbn[0][0] = tb[0].x;
	tbn[0][1] = tb[1].x;
	tbn[0][2] = normal->x;
	tbn[1][0] = tb[0].y;
	tbn[1][1] = tb[1].y;
	tbn[1][2] = normal->y;
	tbn[2][0] = tb[0].z;
	tbn[2][1] = tb[1].z;
	tbn[2][2] = normal->z;
	tbn[3][3] = 1;
	mat_vec_mult(&final_normal, &tbn, &tex_normal);
	normalize_vector(&final_normal);
	mat_vec_mult(&world_normal, &shape->norm_transf, &final_normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}
