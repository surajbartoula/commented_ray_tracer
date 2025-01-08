/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:49:42 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/07 22:26:02 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	loop_over_scene(t_scene *scene, bool r, t_shape *t)
{
	bool	did_collide;
	int		i;
	int		j;

	i = 0;
	did_collide = false;
	while (i < scene->count.shapes)
	{
		j = 0;
		while (j < scene->count.shapes)
		{
			if (i == j)
			{
				j++;
				continue ;
			}
			if (check_collision(&scene->shapes[i], &scene->shapes[j], r, t))
				did_collide = true;
			j++;
		}
		i++;
	}
	return (did_collide);
}

bool	collided(t_scene *scene, bool r, int depth,
		t_shape *t)
{
	bool		did_collide;

	did_collide = false;
	calc_transform(scene);
	did_collide = loop_over_scene(scene, r, t);
	if (!r)
		return (did_collide);
	if (collided(scene, false, 0,  NULL) == true && depth > 0)
		collided(scene, true, depth - 1, NULL);
	return (did_collide);
}

void	sphere_plane_collision_resolution(t_shape *sphere, t_shape *plane)
{
	t_vector	resolution;
	t_vector	origin_to_plane;
	double		distance;

	sub_vector(&origin_to_plane, &sphere->origin, &plane->origin);
	distance = sphere->props.radius - fabs(dot_product(
				&origin_to_plane, &plane->orientation));
	resolution = plane->orientation;
	scale_vector(&resolution, &resolution, distance + 0.001);
	add_vector(&sphere->origin, &sphere->origin, &resolution);
}

bool	sphere_plane_collision(t_shape *sphere, const t_shape *plane)
{
	t_vector	normal;
	double		distance;

	normal = plane->orientation;
	normal.w = 0;
	distance = (dot_product(&normal, &sphere->origin)
			- plane->props.distance_from_origin);
	if (fabs(distance) < sphere->props.radius)
		return (true);
	return (false);
}
//distance = plane's normal vector.sphere's center vector - plane's distance from origin.