/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:02 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:03 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	check_element_count(t_scene *scene)
{
	if (scene->count.ambience > 1 || scene->count.ambience == 0)
	{
		if (scene->count.ambience > 1)
			printf(RED "Error: Scene contains multiple ambient light\n" RESET);
		else
			printf(RED "Error: Scene contains no ambient lights\n" RESET);
		return (free_scene(scene), false);
	}
	if (scene->count.cameras > 1 || scene->count.cameras == 0)
	{
		if (scene->count.cameras > 1)
			printf(RED "Error: Scene contains more than one camera\n" RESET);
		else
			printf(RED "Error: Scene contains no cameras\n" RESET);
		return (free_scene(scene), false);
	}
	return (true);
}

bool	skip_line(char **line, int fd, size_t *line_count)
{
	if (ft_strlen(*line) == 0 || all_whitespace(*line) == true
		|| ft_strncmp(*line, "//", 2) == 0 || ft_strncmp(*line, "#", 1) == 0)
	{
		free(*line);
		*line = ft_strtrim_free(get_next_line(fd), " \t\n");
		*line_count += 1;
		return (true);
	}
	return (false);
}

bool	parse_line(t_scene *scene, char *line, size_t *line_num, int fd)
{
	char	**splitted;

	splitted = ft_split_whitespace(line);
	if (ft_strcmp(splitted[0], "A") == 0)
		parse_ambient(scene, splitted);
	else if (ft_strcmp(splitted[0], "C") == 0)
		parse_camera(scene, splitted);
	else if (ft_strcmp(splitted[0], "L") == 0)
		parse_light(scene, splitted);
	else if (ft_strcmp(splitted[0], "SL") == 0)
		parse_spotlight(scene, splitted);
	else if (is_shape(splitted[0]))
		parse_shape(scene, splitted);
	else if (is_settings(line) == true)
		parse_settings(scene, line, line_num, fd);
	else
		scene->error_flag.unknown_identifier = true;
	if (mem_error(&scene->error_flag))
		print_error(scene, line, *line_num, splitted[0]);
	free(line);
	free_2d_array(splitted);
	return (!mem_error(&scene->error_flag));
}

t_scene	*check_elements(t_scene *scene)
{
	if (check_element_count(scene) == false)
		return (NULL);
	return (scene);
}

t_scene	*parse_scene(int fd)
{
	size_t		line_count;
	t_scene		*scene;
	char		*line;
	bool		status;

	line_count = 1;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (free(line),
			ft_putstr_fd("FD - encountered and Error", 2), NULL);
	while (line != NULL)
	{
		if (skip_line(&line, fd, &line_count) == true)
			continue ;
		status = parse_line(scene, line, &line_count, fd);
		if (status == false)
			return (get_next_line(-1), NULL);
		line = get_next_line(fd);
		line_count++;
	}
	return (check_elements(scene));
}
