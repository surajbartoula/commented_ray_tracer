/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:40:39 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/29 22:43:39 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "lights.h"
# include "scene.h"
# include "mathRT.h"
# include "display.h"
# include "scene.h"
# include "camera.h"

# define NUM_THREADS 16
# define REFLECTION_DEPTH 1

typedef struct s_intersections	t_intersections;

typedef struct s_thread_data
{
	int		tid;
	int		y_start;
	int		y_end;
	int		y_scale_start;
	int		y_scale_end;
	int		max_tid;
	int		height;
	int		width;
	char	*addr;
	t_scene	*scene;
}	t_thread_data;

void		calc_transform(t_scene *scene);
void		calc_cam_transform(t_scene *scene);
void		calculate_orientation(t_mat4 *rot_transform, t_shape *shape);
void		camera_init(t_camera *camera, t_scene *scene);
void		project_rays_on_screen(t_scene *scene);
void		render_scene(t_scene *scene);
t_vector	get_origin(t_shape *shape, t_scene *scene);
void		perspective_projection(t_vector *point, const t_scene *scene);
void		draw_shape_properties(t_shape *shape, t_scene *scene,
				t_vector *proj_origin);
void		draw_shape_coordinates(t_shape *shape, t_scene *scene,
				t_vector *proj_origin);
void		draw_shape_type(t_scene *scene, t_shape *shape,
				t_vector *proj_origin);
bool		is_shadow(t_scene *scene, int light_idx, t_vector *itx_point,
				double *angle);
void		fill_v(t_thread_data *tdata, int th);
void		fill_h(t_thread_data *tdata, int th);
void		reflect_vector(t_vector *res, t_vector *in_vector,
				t_vector *normal);
t_color		shade_point(t_intersections *arr, t_scene *scene, t_ray *ray);
void		render_shape_marker(t_scene *scene);
t_color		render_pixel(double x, double y, t_intersections *arr,
				t_thread_data *tdata);

#endif