/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:54:46 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/07 09:51:25 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/miniRT.h"

static int	read_file(int argc, char *argv[])
{
	char	*file_name;
	int		fd;

	if (argc != 2)
		return (invalid_argument(), -1);
	file_name = argv[1];
	if (ft_strlen(file_name) < 3
		|| ft_strncmp(&file_name[ft_strlen(file_name) - 3], ".rt", 4) != 0)
		return (wrong_file_format(), -1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (opening_file_failed(file_name), -1);
	return (fd);
}

void	scene_init(t_scene *scene, t_display *display)
{
	scene->disp = display;
	setup_hooks(scene);
	camera_init(&scene->cam, scene);
	//Calculate angles related to camera's direction in 3D space
	scene->cam.theta = atan(scene->cam.dir.z / scene->cam.dir.x);
	scene->cam.pi = acos(scene->cam.dir.y); //polar angle
	//calculate camera transformation matrix
	calc_transform(scene);
	collided(scene, true, 10, NULL);
	render_scene(scene);
}

int	main(int argc, char *argv[])
{
	t_scene		*scene;
	t_display	dsply;
	int			fd;

	fd = read_file(argc, argv);
	if (fd == -1)
		return (EXIT_FAILURE);
	scene = parse_scene(fd);
	if (!scene)
		return (close(fd), free_scene(scene), EXIT_FAILURE);
	close(fd);
	init_settings(&scene->settings);
	init_display(&dsply, &scene->settings);
	if (dsply.mlx == NULL)
		return (close(fd), free_scene(scene), EXIT_FAILURE);
	scene_init(scene, &dsply);
	mlx_loop(dsply.mlx);
}
