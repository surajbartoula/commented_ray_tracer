/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_validation1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:10 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:11 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_strcmp_case(const char *s1, const char *s2)
{
	while (ft_tolower(*s1) != '\0' && ft_tolower(*s2) != '\0')
	{
		if (ft_tolower(*s1) > ft_tolower(*s2))
			return (1);
		if (ft_tolower(*s1) < ft_tolower(*s2))
			return (-1);
		s1++;
		s2++;
	}
	if (*s1 != '\0')
		return (1);
	if (*s2 != '\0')
		return (-1);
	return (0);
}

bool	is_settings(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '{')
			return (true);
		if (ft_isspace(line[i]) == false)
			return (false);
		i++;
	}
	return (false);
}

bool	is_valid_key(const char *key)
{
	if (key != NULL && (ft_strcmp(key, "reflectiveness") == 0
			|| ft_strcmp(key, "diffuse") == 0
			|| ft_strcmp(key, "specular") == 0
			|| ft_strcmp(key, "shininess") == 0
			|| ft_strcmp(key, "rotX") == 0
			|| ft_strcmp(key, "rotY") == 0
			|| ft_strcmp(key, "rotZ") == 0
			|| ft_strcmp(key, "scaleX") == 0
			|| ft_strcmp(key, "scaleY") == 0
			|| ft_strcmp(key, "scaleZ") == 0
			|| ft_strcmp(key, "color") == 0
			|| ft_strcmp(key, "normal_texture") == 0
			|| ft_strcmp(key, "diffuse_texture") == 0
			|| ft_strcmp(key, "tile_texture") == 0
		))
		return (true);
	return (false);
}

bool	is_valid_color(const char *color)
{
	if (ft_strcmp_case(color, "blue") == 0
		|| ft_strcmp_case(color, "red") == 0
		|| ft_strcmp_case(color, "purple") == 0
		|| ft_strcmp_case(color, "green") == 0
		|| ft_strcmp_case(color, "yellow") == 0
		|| ft_strcmp_case(color, "pink") == 0
		|| ft_strcmp_case(color, "black") == 0
		|| ft_strcmp_case(color, "gray") == 0
		|| ft_strcmp_case(color, "white") == 0
		|| ft_strcmp_case(color, "cyan") == 0
		|| ft_strcmp_case(color, "orange") == 0)
		return (true);
	printf(COLOR_SETTING_ERROR, "color", color, color);
	return (false);
}
