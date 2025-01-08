/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:31 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:32 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	parse_cylinder_props(t_shape *shape, t_scene *scene, char **splitted)
{
	bool	success;

	success = true;
	shape->props.radius = ft_atof(splitted[3], &success) / 2;
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.shape.diameter_other = true;
	if (mem_error(&scene->error_flag) == false && shape->props.radius <= 0.0)
		scene->error_flag.shape.diameter_range = true;
	shape->props.height = ft_atof(splitted[4], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.shape.height_other = true;
	if (mem_error(&scene->error_flag) == false && shape->props.height <= 0.0)
		scene->error_flag.shape.height_range = true;
	parse_color(&shape->props.color, splitted[5],
		&scene->error_flag.shape.color);
}

void	parse_cylinder(t_scene *scene, t_shape *shape, char **splitted)
{
	bool	success;

	success = true;
	shape->type = CYLINDER;
	if (split_count(splitted) != 6)
	{
		scene->error_flag.shape.other = true;
		return ;
	}
	parse_coordinates(&shape->origin, splitted[1], &success);
	if (mem_error(&scene->error_flag) == false && success == false)
		scene->error_flag.shape.origin = true;
	parse_orientation(&shape->orientation, splitted[2],
		&scene->error_flag.shape.orient);
	if (mem_error(&scene->error_flag))
		return ;
	parse_cylinder_props(shape, scene, splitted);
	if (mem_error(&scene->error_flag))
		return ;
}

void	parse_cone(t_scene *scene, t_shape *shape, char **splitted)
{
	parse_cylinder(scene, shape, splitted);
	shape->type = CONE;
}

bool	parse_shape(t_scene *scene, char **splitted)
{
	if (scene->count.shapes == SHAPE_MAX)
		return (scene->error_flag.shape.max_shapes = true, false);
	if (scene->shapes == NULL)
		scene->shapes = ft_calloc(SHAPE_MAX, sizeof(t_shape));
	if (scene->shapes == NULL)
		return (false);
	if (ft_strcmp(splitted[0], "sp") == 0)
		parse_sphere(scene, &scene->shapes[scene->count.shapes], splitted);
	else if (ft_strcmp(splitted[0], "pl") == 0)
		parse_plane(scene, &scene->shapes[scene->count.shapes], splitted);
	else if (ft_strcmp(splitted[0], "cy") == 0)
		parse_cylinder(scene, &scene->shapes[scene->count.shapes], splitted);
	else if (ft_strcmp(splitted[0], "cu") == 0)
		parse_cube(scene, &scene->shapes[scene->count.shapes], splitted);
	else if (ft_strcmp(splitted[0], "co") == 0)
		parse_cone(scene, &scene->shapes[scene->count.shapes], splitted);
	if (mem_error(&scene->error_flag))
		return (false);
	init_shape(&scene->shapes[scene->count.shapes], scene);
	return (true);
}
