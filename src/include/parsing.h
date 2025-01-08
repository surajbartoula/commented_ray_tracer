/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:13:45 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 15:28:20 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"

typedef struct s_color_error	t_color_err;
struct s_color_error
{
	bool	r;
	bool	g;
	bool	b;
	bool	other;
};

typedef struct s_orient_err		t_orient_err;
struct s_orient_err
{
	bool	x;
	bool	y;
	bool	z;
	bool	zero;
	bool	other;
};

typedef struct s_ambient_err	t_ambient_err;
struct s_ambient_err
{
	bool			intensity_other;
	bool			intensity_range;
	bool			other;
	t_color_err		color;
};

typedef struct s_shape_errors
{
	bool			max_shapes;
	bool			diameter_range;
	bool			diameter_other;
	bool			height_range;
	bool			height_other;
	bool			origin;
	bool			side_len_other;
	bool			side_len_range;
	bool			other;
	t_color_err		color;
	t_orient_err	orient;
}	t_shape_errors;

typedef struct s_light_errors
{
	bool			intensity_other;
	bool			intensity_range;
	bool			max_lights;
	bool			other;
	bool			coords;
	t_orient_err	orient;
	bool			angle_other;
	bool			angle_range;
	t_color_err		color;
}	t_light_errors;

typedef struct s_cam_err
{
	bool			other;
	bool			coord;
	bool			fov_other;
	bool			fov_range;
	bool			up_vector;
	t_orient_err	dir;
}	t_cam_err;

typedef struct s_error_flags
{
	t_ambient_err	ambient;
	t_cam_err		cam;
	t_light_errors	light;
	t_shape_errors	shape;
	bool			unknown_identifier;
	bool			settings_err;
}	t_error_flags;

typedef struct s_shape_err
{
	bool			max_shapes;
	bool			diameter_range;
	bool			diameter_other;
	bool			height_range;
	bool			height_other;
	bool			origin;
	bool			side_len_other;
	bool			side_len_range;
	bool			other;
	t_color_err		color;
	t_orient_err	orient;
}	t_shape_err;

void		invalid_argument(void);
void		wrong_file_format(void);
void		opening_file_failed(char *file_name);
bool		print_ambient_light_error(t_ambient_err *err, const char *line,
				int line_num);
bool		print_light_error(t_light_errors *err, const char *line,
				int line_num);
bool		print_shape_error(t_shape *shape, t_shape_errors *error,
				const char *line, int line_num);
bool		mem_error(t_error_flags *err);
bool		print_sphere_error(t_shape_errors *err, const char *line,
				int line_num);
bool		print_cube_error(t_shape_errors *err, const char *line,
				int line_num);
bool		print_plane_error(t_shape_errors *err, const char *line,
				int line_num);
bool		print_cylinder_error(t_shape_errors *err, const char *line,
				int line_num);
bool		print_cone_error(t_shape_errors *err, const char *line,
				int line_num);
#endif