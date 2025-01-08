/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:11:29 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/03 14:57:45 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vector	*sphere_mod(t_vector *vec, double phi, double theta, double r)
{
	vec->x = r * sin(phi) * cos(theta);
	vec->z = r * sin(phi) * sin(theta);
	vec->y = r * cos(phi);
	vec->w = 0;
	return (vec);
}

void	light_controls_continue(t_scene *scene, t_light *light)
{
	if (scene->keys_held.shift == false && scene->keys_held.plus == true)
		light->intensity = min(light->intensity + 0.05, 5);
	if (scene->keys_held.shift == false && scene->keys_held.minus == true)
		light->intensity = max(light->intensity - 0.05, 0);
	if (scene->keys_held.up == true || scene->keys_held.down == true)
		rotate_x(scene, &scene->lights[scene->light_idx].added_rots,
			-DEG_TO_RAD * 2);
	if (scene->keys_held.left == true || scene->keys_held.right == true)
		rotate_y(scene, &scene->lights[scene->light_idx].added_rots,
			-DEG_TO_RAD * 2);
	if (scene->keys_held.shift == true && scene->keys_held.plus == true)
		scene->lights[scene->light_idx].theta += 0.02;
	if (scene->keys_held.shift == true && scene->keys_held.minus == true)
	{
		if (scene->lights[scene->light_idx].theta > 0.1)
			scene->lights[scene->light_idx].theta -= 0.02;
	}
	normalize_vector(&scene->lights[scene->light_idx].direction);
}

void	light_controls(t_scene *scene)
{
	t_vector	offset;
	t_light		*light;

	light = &scene->lights[scene->light_idx];
	ft_bzero(&offset, sizeof(t_vector));
	if (scene->keys_held.w)
		sphere_mod(&offset, M_PI / 2, scene->cam.theta, 0.2);
	if (scene->keys_held.s)
		sphere_mod(&offset, M_PI / 2, scene->cam.theta, -0.2);
	if (scene->keys_held.w || scene->keys_held.s)
		add_vector(&light->position, &light->position, &offset);
	if (scene->keys_held.q == true)
		light->position.y += 0.3;
	if (scene->keys_held.e == true)
		light->position.y -= 0.3;
	if (scene->keys_held.a)
		sphere_mod(&offset, M_PI_2, scene->cam.theta + M_PI_2, 0.2);
	if (scene->keys_held.d)
		sphere_mod(&offset, M_PI_2, scene->cam.theta - M_PI_2, 0.2);
	if (scene->keys_held.a || scene->keys_held.d)
		add_vector(&light->position, &light->position, &offset);
	light_controls_continue(scene, light);
}
