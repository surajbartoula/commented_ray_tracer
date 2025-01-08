/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:39:10 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/01 17:22:30 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIONS_H
# define INTERACTIONS_H

# include <stdbool.h>
# include "miniRT.h"

typedef struct s_scene	t_scene;
typedef struct s_ray	t_ray;

typedef struct s_keys	t_keys;
struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	q;
	bool	e;
	bool	plus;
	bool	minus;
	bool	tab;
	bool	c;
	bool	shift;
	bool	x;
	bool	y;
	bool	z;
	bool	o;
};

# define CAM_SPEED 0.5
# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define SPACE 49
# define RETURN 36
# define SHIFT 257
# define TAB 48
# define LEFT_MOUSE_DOWN 1
# define PLUS 24
# define MINUS 27
# define O 31
# define E 14
# define P 35
# define C 8
# define R 15
# define M 46
# define Q 12
# define ONE_KEY 18
# define TWO_KEY 19
# define THREE_KEY 20
# define FOUR_KEY 21
# define FIVE_KEY 23
# define SIX_KEY 22
# define SEVEN_KEY 26
# define EIGHT_KEY 28
# define NINE_KEY 25
# define X 7
# define J 38
# define Y 16
# define Z 6
# define L 37
# define H 4
# define T 17

void		setup_hooks(t_scene *scene);
int			mouse_down(int key_code, int x, int y, t_scene *scene);
int			mouse_up(int key_code, int x, int y, t_scene *scene);
void		mouse_move(t_scene *scene);
int			mouse_rotate(t_scene *scene);
int			render_loop(t_scene *scene);
void		drag_along_plane(t_scene *scene, t_ray *mouse_selection);
void		rotate_along_mouse_axis(t_scene *scene);
void		mouse_select(t_scene *scene, double x, double y);
void		transform_object(t_scene *scene);
void		free_textures(t_scene *scene);
void		free_scene(t_scene *scene);
void		toggle_keys_held(int key, t_scene *scene, bool onoff);
void		select_shape(int key, t_scene *scene);
void		spawn_shape(t_scene *scene);
void		toggle_shape(t_scene *scene);
void		toggle_edit_mode(int key, t_scene *scene);
void		handle_color_change(int key, t_scene *scene, t_color *color);
void		rest_press(int key, t_scene *scene);
void		light_controls(t_scene *scene);
void		move_object_v(t_scene *scene, t_shape *shape);
void		move_object_h(t_scene *scene, t_shape *shape);
void		move_object_fwd(t_scene *scene, t_shape *shape);
void		change_height(t_scene *scene, t_shape *shape);
void		scale_object(t_scene *scene, t_shape *shape);
void		look_at_animation(t_scene *scene);
void		toggle_reflections(t_scene *scene);
void		look_at(t_scene *scene, t_shape *shape);
void		camera_controls(t_scene *scene);
void		rotate_object(t_scene *scene);
void		scale_cube_sides(t_scene *scene, t_shape *shape);
void		ray_from_cam(t_ray *ray, const t_camera *cam, double x, double y);

#endif