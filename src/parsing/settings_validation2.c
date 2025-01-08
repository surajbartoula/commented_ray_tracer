/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_validation2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:13 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:14 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	check_value(const char *key, const char *val, double min, double max)
{
	bool	status;
	double	parsed_value;

	status = true;
	if (ft_strcmp_case(key, "diffuse_texture") == 0
		|| ft_strcmp_case(key, "normal_texture") == 0
	)
	{
		if (ft_strnstr(val, ".ppm\"", ft_strlen(val)) == NULL
			|| ft_strcmp(&val[ft_strlen(val) - 5], ".ppm\"") != 0)
		{
			printf(INVALID_PROP_VALUE, key, val, val);
			printf(YELLOW"Only valid .ppm files are supported\n"RESET);
			return (false);
		}
		return (true);
	}
	if (is_num(val, true) == false)
		return (!printf(INVALID_PROP_VALUE, key, val, val));
	parsed_value = ft_atof(val, &status);
	if (status == false || parsed_value < min || parsed_value > max)
		return (!printf(INVALID_PROPERTY_RANGE, key, val, key, min, max));
	return (true);
}

bool	is_valid_val(const char *key, const char *val)
{
	double	min;
	double	max;

	if (val == NULL || ft_strlen(val) == 0)
		return (false);
	min = 0.0;
	max = 1.0;
	if (ft_strcmp(key, "shininess") == 0)
		return (check_value(key, val, 10, 400));
	if (ft_strncmp(key, "rot", 3) == 0)
		return (check_value(key, val, 0.0, 360));
	if (ft_strncmp(key, "scale", 5) == 0)
		return (check_value(key, val, 0.1, 50));
	if (ft_strcmp(key, "tile_texture") == 0)
		return (check_value(key, val, 1, 16));
	if (ft_strcmp(key, "color") == 0)
		return (is_valid_color(val));
	return (check_value(key, val, min, max));
}
