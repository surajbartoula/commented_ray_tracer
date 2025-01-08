/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:45 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:46 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	read_rest_of_header(char *buff, int *w, int *h, int fd)
{
	char	**tokens;
	int		bytes;

	tokens = ft_split(buff, ' ');
	if (tokens == NULL)
		return (-1);
	if (split_count(tokens) != 2)
	{
		free_2d_array(tokens);
		return (-1);
	}
	*w = ft_atoi(tokens[0]);
	*h = ft_atoi(tokens[1]);
	free_2d_array(tokens);
	if (*w <= 0 || *h <= 0)
		return (-1);
	bytes = read(fd, buff, 4);
	if (bytes <= 0)
		return (-1);
	return (0);
}

int	read_ppm_header(int fd, int *w, int *h)
{
	char	buff[1001];
	int		bytes;
	int		i;
	char	ch;

	ft_bzero(buff, 1001);
	bytes = read(fd, buff, 3);
	buff[bytes] = '\0';
	if (bytes <= 0 || ft_strncmp(buff, "P6", 2) != 0)
		return (-1);
	i = 0;
	ft_bzero(buff, 1001);
	bytes = read(fd, &ch, 1);
	while (bytes > 0 && ch != '\n' && i < 1000)
	{
		buff[i] = ch;
		bytes = read(fd, &ch, 1);
		i++;
	}
	if (i == 1000 || bytes == 0)
		return (-1);
	buff[i] = '\0';
	return (read_rest_of_header(buff, w, h, fd));
}

t_color	read_ppm_color(unsigned char *buff, int idx)
{
	t_color			color;

	color.a = 0;
	color.r = buff[idx * 3] / 255.0;
	color.g = buff[idx * 3 + 1] / 255.0;
	color.b = buff[idx * 3 + 2] / 255.0;
	return (color);
}

t_color	**fill_colors_array(int bytes_read, char *img_path, unsigned char *buff,
			t_shape *shape)
{
	int		i;
	int		j;
	t_color	**colors;

	if (bytes_read < shape->text_height * shape->tex_width * 3)
		return (free(buff), free(img_path),
			(void)printf("Error reading texture file `%s`\n"RESET,
				img_path), NULL);
	buff[bytes_read] = '\0';
	colors = ft_calloc((shape->text_height + 1), sizeof(t_color *));
	i = 0;
	while (i < shape->text_height)
		colors[i++] = malloc((shape->tex_width + 1) * sizeof(t_color));
	i = -1;
	while (++i < shape->text_height)
	{
		j = 0;
		while (j < shape->tex_width)
		{
			colors[i][j] = read_ppm_color(buff, i * shape->tex_width + j);
			j++;
		}
	}
	return (free(buff), free(img_path), colors);
}
