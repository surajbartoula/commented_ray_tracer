/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:12:59 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 18:07:44 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	ray_from_cam(t_ray *ray, const t_camera *cam, double x, double y)
{
	double		world_x;
	double		world_y;
	t_vector	pixel;
	t_vector	world_point;
	t_vector	center;

	world_x = cam->half_w - (x) * cam->pixel_sz;
	world_y = cam->half_h - (y) * cam->pixel_sz;
	world_point.x = world_x;
	world_point.y = world_y;
	world_point.z = -1;
	world_point.w = 1;
	mat_vec_mult(&pixel, &cam->inv_trans, &world_point);
	ft_bzero(&center, sizeof(t_vector));
	center.w = 1;
	mat_vec_mult(&ray->origin, &cam->inv_trans, &center);
	sub_vector(&ray->dir, &pixel, &ray->origin);
	ray->dir.w = 0;
	normalize_vector(&ray->dir);
}
