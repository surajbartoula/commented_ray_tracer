/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:24 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:25 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	parse_split_settings(t_scene *scene, char **settings)
{
	int		line_idx;
	char	**key_val;

	line_idx = 0;
	while (settings[line_idx] != NULL)
	{
		if (check_colons(settings[line_idx]) == false)
			return (false);
		key_val = ft_split(settings[line_idx], ':');
		if (check_key_val_split(key_val, settings, line_idx) == false)
			return (false);
		key_val[0] = ft_strtrim_free(key_val[0], " \n\t");
		key_val[1] = ft_strtrim_free(key_val[1], " \n\t");
		if (check_key_vals(key_val, settings, scene, line_idx) == false)
			return (false);
		free_2d_array(key_val);
		line_idx++;
	}
	return (true);
}

bool	parse_settings(t_scene *scene, const char *settings_start,
	size_t *line_num, int fd)
{
	char	*settings_str;
	char	**settings;

	if (scene->count.shapes == 0)
	{
		printf(SETTINGS_NO_SHAPE, *line_num);
		scene->error_flag.settings_err = true;
		return (false);
	}
	settings_str = get_settings_str(line_num, fd, settings_start);
	if (settings_str == NULL)
	{
		scene->error_flag.settings_err = true;
		return (false);
	}
	settings = ft_split(settings_str, ',');
	free(settings_str);
	if (parse_split_settings(scene, settings) == false)
	{
		scene->error_flag.settings_err = true;
		free_2d_array(settings);
		return (false);
	}
	free_2d_array(settings);
	return (true);
}
