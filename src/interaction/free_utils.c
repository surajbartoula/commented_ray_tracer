/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:40:22 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/05 18:30:42 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	free_scene(t_scene *scene)
{
	if (scene == NULL)
		return ;
	if (scene->disp != NULL && scene->disp->mlx != NULL)
	{
		mlx_destroy_image(scene->disp->mlx, scene->disp->display_img);
		mlx_destroy_image(scene->disp->mlx, scene->disp->render_img);
		mlx_destroy_image(scene->disp->mlx, scene->disp->edit_img);
		mlx_destroy_window(scene->disp->mlx, scene->disp->win);
		free(scene->disp->mlx);
	}
	free_textures(scene);
	if (scene->lights != NULL)
		free(scene->lights);
	if (scene->shapes != NULL)
		free(scene->shapes);
	free(scene);
}
