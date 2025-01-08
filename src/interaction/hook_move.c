/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:47:42 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:56:48 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	move_object_h(t_scene *scene, t_shape *shape)
{
	t_vector	offset;

	ft_bzero(&offset, sizeof(t_vector));
	if (scene->keys_held.a)
	{
		sphere_mod(&offset, M_PI_2, scene->cam.theta + M_PI_2, 0.2);
	}
	if (scene->keys_held.d)
	{
		sphere_mod(&offset, M_PI_2, scene->cam.theta - M_PI_2, 0.2);
	}
	add_vector(&shape->origin, &shape->origin, &offset);
}

void	move_object_v(t_scene *scene, t_shape *shape)
{
	t_vector	offset;

	ft_bzero(&offset, sizeof(t_vector));
	if (scene->keys_held.q)
	{
		offset.y = 0.2;
	}
	if (scene->keys_held.e)
	{
		offset.y = -0.2;
	}
	add_vector(&shape->origin, &shape->origin, &offset);
}

void	move_object_fwd(t_scene *scene, t_shape *shape)
{
	t_vector	offset;

	ft_bzero(&offset, sizeof(t_vector));
	if (scene->keys_held.w)
	{
		sphere_mod(&offset, M_PI / 2, scene->cam.theta, 0.2);
	}
	if (scene->keys_held.s)
	{
		sphere_mod(&offset, M_PI / 2, scene->cam.theta, -0.2);
	}
	add_vector(&shape->origin, &shape->origin, &offset);
}
