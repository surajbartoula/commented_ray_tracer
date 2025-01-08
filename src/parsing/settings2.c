/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:21 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:22 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_color	parse_color_value(const char *str)
{
	int		hex_color;

	if (ft_strcmp_case(str, "blue") == 0)
		hex_color = 0x228be6;
	if (ft_strcmp_case(str, "red") == 0)
		hex_color = 0xf03e3e;
	if (ft_strcmp_case(str, "purple") == 0)
		hex_color = 0x7048e8;
	if (ft_strcmp_case(str, "green") == 0)
		hex_color = 0x37b24d;
	if (ft_strcmp_case(str, "yellow") == 0)
		hex_color = 0xf59f00;
	if (ft_strcmp_case(str, "pink") == 0)
		hex_color = 0xe64980;
	if (ft_strcmp_case(str, "black") == 0)
		hex_color = 0x212529;
	if (ft_strcmp_case(str, "gray") == 0)
		hex_color = 0x6d656d;
	if (ft_strcmp_case(str, "white") == 0)
		hex_color = 0xf8f9fa;
	if (ft_strcmp_case(str, "cyan") == 0)
		hex_color = 0x15aabf;
	if (ft_strcmp_case(str, "orange") == 0)
		hex_color = 0xf76707;
	return (int_to_color(hex_color));
}

bool	parse_rest_of_settings(t_shape *shape, char **key_val)
{
	bool	success;

	if (ft_strcmp("color", key_val[0]) == 0)
		shape->props.color = parse_color_value(key_val[1]);
	if (ft_strcmp("diffuse_texture", key_val[0]) == 0)
	{
		free_texture(shape, shape->diffuse_tex);
		shape->diffuse_tex = parse_texture(key_val[1], shape);
		if (shape->diffuse_tex == NULL)
			return (false);
	}
	if (ft_strcmp("normal_texture", key_val[0]) == 0)
	{
		free_texture(shape, shape->normal_tex);
		shape->normal_tex = parse_texture(key_val[1], shape);
		if (shape->normal_tex == NULL)
			return (false);
	}
	if (ft_strcmp("tile_texture", key_val[0]) == 0)
		shape->tex_tile = ft_atol(key_val[1], &success);
	return (true);
}

bool	parse_setting(t_shape *shape, char **key_val)
{
	bool	success;

	if (ft_strcmp("reflectiveness", key_val[0]) == 0)
		shape->props.reflectiveness = ft_atof(key_val[1], &success);
	if (ft_strcmp("diffuse", key_val[0]) == 0)
		shape->props.diffuse = ft_atof(key_val[1], &success);
	if (ft_strcmp("specular", key_val[0]) == 0)
		shape->props.specular = ft_atof(key_val[1], &success);
	if (ft_strcmp("shininess", key_val[0]) == 0)
		shape->props.shininess = ft_atof(key_val[1], &success);
	if (ft_strcmp("rotX", key_val[0]) == 0)
		shape->props.rot.x = ft_atol(key_val[1], &success);
	if (ft_strcmp("rotY", key_val[0]) == 0)
		shape->props.rot.y = ft_atol(key_val[1], &success);
	if (ft_strcmp("rotZ", key_val[0]) == 0)
		shape->props.rot.z = ft_atol(key_val[1], &success);
	if (ft_strcmp("scaleX", key_val[0]) == 0)
		shape->props.scale.x = ft_atof(key_val[1], &success);
	if (ft_strcmp("scaleY", key_val[0]) == 0)
		shape->props.scale.y = ft_atof(key_val[1], &success);
	if (ft_strcmp("scaleZ", key_val[0]) == 0)
		shape->props.scale.z = ft_atof(key_val[1], &success);
	if (parse_rest_of_settings(shape, key_val) == false)
		return (false);
	return (true);
}
