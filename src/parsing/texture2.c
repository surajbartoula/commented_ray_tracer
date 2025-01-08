/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:50 by allan             #+#    #+#             */
/*   Updated: 2025/01/05 18:43:41 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_color	**parse_texture(char *img_path, t_shape *shape)
{
	int				bytes_read;
	int				fd;
	unsigned char	*buff;

	img_path = ft_strtrim(img_path, "\"");
	fd = open(img_path, O_RDONLY);
	if (fd == -1)
	{
		free(img_path);
		printf("Error coming from fd-1\n");
		return ((void) printf("Error reading texture file `%s`\n"RESET,
				img_path), NULL);
	}
	if (read_ppm_header(fd, &shape->tex_width, &shape->text_height) == -1)
	{
		close(fd);
		free(img_path);
		printf("Error coming from ppm_header\n");
		return ((void) printf("Error reading texture file `%s`\n"RESET,
				img_path), NULL);
	}
	buff = malloc(shape->text_height * shape->tex_width * 3 + 1);
	bytes_read = read(fd, buff, shape->text_height * shape->tex_width * 3);
	close(fd);
	return (fill_colors_array(bytes_read, img_path, buff, shape));
}
