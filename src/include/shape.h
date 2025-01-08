/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:30:27 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/06 23:26:10 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "mathRT.h"

typedef enum e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	CUBE,
	TRIANGLE
}	t_shape_type;

typedef enum e_pattern_type
{
	NONE,
	STRIPE,
	CHECKER_BOARD,
	GRADIENT,
	RING
}	t_pattern_type;

typedef struct s_shape_props
{
	bool			highlighted;
	double			radius;
	double			radius_squared;
	double			height;
	double			diffuse;
	double			specular;
	double			shininess;
	double			reflectiveness;
	double			distance_from_origin;
	t_vector		cyl_normal;
	t_color			color;
	t_vector		rot;
	t_vector		scale;
	t_pattern_type	pattern_type;
}	t_props;

typedef struct s_shape
{
	t_shape_type	type;
	int				id;
	t_props			props;
	t_vector		origin;
	t_vector		orientation;
	t_mat4			transf; //transformation matrix
	t_mat4			inv_transf; //inverse transformation matrix
	t_mat4			norm_transf; //normal transformation matrix
	t_mat4			added_rots; //added rotations
	t_color			**diffuse_tex;
	t_color			**normal_tex; //surface features like bumps, wrinkles etc
	int				tex_width;
	int				text_height;
	int				tex_tile; //how many times the tiles will repeat over the shape's surface
	unsigned int	mlx_color;
}	t_shape;
#endif