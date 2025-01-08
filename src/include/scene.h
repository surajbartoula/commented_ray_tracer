/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:28:47 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/27 14:24:58 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "interactions.h"
# include "parsing.h"
# include "mathRT.h"
# include "lights.h"
# include <semaphore.h>
# include "display.h"
# include "intersection.h"
# include <stdbool.h>

typedef struct s_ambient
{
	double	intensity;
	t_color	color;
}	t_ambient;

typedef struct s_mouse
{
	bool	active;
	bool	toggle;
	int		prev_x;
	int		prev_y;
	int		x;
	int		y;
	int		key;
}	t_mouse;

typedef struct s_el_count
{
	int		ambience;
	int		cameras;
	int		lights;
	int		shapes;
}	t_el_count;

typedef struct s_settings
{
	int			disp_h;
	int			disp_w;
	int			render_h;
	int			render_w;
	int			edit_h;
	int			edit_w;
	bool		camera_mode;
	bool		edit_mode;
	bool		light_mode;
	int			reflection_depth;
	double		edit_scale;
	double		render_scale;
	bool		collisions;
	bool		help_menu;
	bool		supersampling;
}	t_settings;

typedef struct s_look
{
	t_vector	final_pos;
	t_vector	initial_orientation;
	t_vector	final_dir;
	t_vector	current_dir;
	t_vector	pos_diff;
	t_vector	dir_diff;
	bool		trigger;
	int			step_num;
	int			step_amount;
}	t_look;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		cam;
	t_light			*lights;
	t_shape			*shapes;
	t_el_count		count;
	t_display		*disp;
	t_keys			keys_held;
	t_settings		settings;
	int				shape_idx;
	int				light_idx;
	t_look			look_at;
	t_mouse			mouse;
	t_error_flags	error_flag;
}	t_scene;

void			cylindrical_map(double *x, double *y, t_vector *comp);
void			cubicle_mapping(double *x, double *y, t_vector *p);
void			mapping_right(double *x, double *y, t_vector *p);
void			mapping_left(double *x, double *y, t_vector *p);
void			mapping_up(double *x, double *y, t_vector *p);
void			mapping_down(double *x, double *y, t_vector *p);
void			mapping_front(double *x, double *y, t_vector *p);
bool			is_toggle_key(int key, t_scene *scene);
void			render_marker(t_scene *scene, int x, int y, int color);
void			init_settings(t_settings *settings);
void			init_display(t_display *display, t_settings *settings);

#endif
