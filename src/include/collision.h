/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:04:23 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/30 13:33:21 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include "miniRT.h"

# define MAX_SIMPLEX_SIZE 4

typedef struct s_scene							t_scene;
typedef struct s_box_axes						t_box_axes;
typedef struct s_cylinder_collision_data		t_cy_collision_data;
typedef struct s_cylinder_plane_collision_math	t_colmath;
typedef struct s_cylinder_sphere_data			t_cy_sp_data;
typedef struct s_collision_inputs				t_collision_inputs;
typedef struct s_simplex						t_simplex;
typedef struct s_triangledata					t_triangledata;
typedef struct s_tetrahedron_data				t_tetrahedron_data;

struct s_box_axes
{
	t_vector	b1_u[3];
	t_vector	b2_u[3];
	t_mat4		rot;
	t_mat4		abs_rot;
	double		t[3];
	t_vector	center_distance;
	double		b1_e[3];
	double		b2_e[3];
	double		res_distance;
	t_vector	res_axis;
	double		ra;
	double		rb;
};

struct s_cylinder_collision_data
{
	t_vector	cylinder_normal;
	t_vector	top_cap_center;
	t_vector	bottom_cap_center;
	t_vector	cap_center;
	t_vector	resolution;
};

struct s_cylinder_plane_collision_math
{
	double		d;
	double		t;
	double		dist;
	t_ray		ray;
	t_vector	point_on_splane;
	t_vector	dir;
	t_vector	end_point;
	t_vector	plane_to_end_point;
	t_vector	resolution;
	t_vector	center_to_point;
};

struct s_cylinder_sphere_data
{
	t_vector	cylinder_to_sphere;
	t_vector	up_vector;
	double		v_dist;
	t_vector	cap_to_sphere;
	double		dist;
	double		v_cap_distance;
	double		h_cap_distance;
	t_vector	dir;
	t_vector	center_delta;
	t_vector	edge;
	t_vector	center_adjusted;
	double		edge_distance;
};

struct s_collision_inputs
{
	t_shape	*cylinder;
	t_shape	*sphere;
	bool	resolve;
};

struct s_simplex
{
	t_vector	arr[4];
	int			size;
};

struct s_triangledata
{
	t_vector	pb;
	t_vector	pc;
	t_vector	po;
	t_vector	pbc;
	t_vector	pbc_pc;
	t_vector	pb_pbc;
};

struct s_tetrahedron_data
{
	t_vector	ab;
	t_vector	ac;
	t_vector	ad;
	t_vector	ao;
	t_vector	abc;
	t_vector	acd;
	t_vector	adb;
};

bool		test_axis_overlap(t_box_axes *ba, t_shape *b1, t_shape *b2,
				int axis);
void		compute_center_distance(t_box_axes *ba, t_shape *b1, t_shape *b2);
void		calculate_rotation_matrices(t_box_axes *ba);
void		extract_unit_vectors(t_shape *shape, t_vector *unit_vectors);
void		initialize_box_axes(t_box_axes *ba);
bool		test_box_axes(t_shape *b1, t_shape *b2, t_vector *resolution);
bool		check_collision(t_shape *shape1, t_shape *shape2, bool resolve,
				t_shape *transformed_shape);
void		handle_secondary_plane_case(t_cy_collision_data *cy_data,
				t_shape *cylinder, t_shape *plane);
void		cylinder_plane_collision_resolution(t_shape *cylinder,
				t_shape *plane);
bool		cylinder_sphere_collision(t_shape *cylinder, t_shape *sphere,
				bool resolve);
t_vector	cube_furthest_point(const t_vector *dir, const t_shape *box);
void		fill_vtx0(t_vector *vtx);
void		fill_vtx1(t_vector *vtx);
void		fill_vtx2(t_vector *vtx);
void		fill_vtx3(t_vector *vtx);
void		fill_vtx4(t_vector *vtx);
void		fill_vtx5(t_vector *vtx);
void		fill_vtx6(t_vector *vtx);
void		fill_vtx7(t_vector *vtx);
void		add_to_simplex(t_simplex *sim, t_vector *point);
t_vector	triple_cross_product(t_vector *v1, t_vector *v2,
				const t_vector *v3);
bool		triangle_on_origin(t_simplex *simplex, t_vector *dir);
bool		line_on_origin(t_simplex *simplex, t_vector *dir);
bool		tetrahedron_on_origin(t_simplex *simplex, t_vector *dir);
bool		handle_simplex(t_simplex *sim, t_vector *dir);
bool		collided(t_scene *scene, bool r, int depth,
				t_shape *t);
void		render_scene(t_scene *scene);
void		exec_thread(t_thread_data *tdata, void *func);
void		init_thread_data(t_thread_data *tdata, t_scene *scene);
bool		check_spotlight(t_scene *scene, int light_idx, t_ray *ray,
				double *angle);
bool		gjk(t_shape *s1, t_shape *s2);
bool		sphere_plane_collision(t_shape *sphere, const t_shape *plane);
bool		cylinder_plane_collision(t_shape *cylinder, t_shape *plane);
void		sphere_plane_collision_resolution(t_shape *sphere, t_shape *plane);
bool		sphere_sphere_collision(const t_shape *sphere1,
				const t_shape *sphere2);
bool		box_box_collision(t_shape *box1, t_shape *box2, bool resolve);
bool		cone_cone_collision(t_shape *co1, t_shape *co2);
bool		cylinder_cylinder_collision(t_shape *cyl1, t_shape *cyl2);
t_vector	closest_point_on_box(const t_vector *point, const t_shape *box);
bool		sphere_box_collision(t_shape *box, t_shape *sphere,
				bool box_sphere, bool resolve);
void		transform_ray(t_ray *transformed_ray, const t_ray *ray,
				const t_shape *shape);
void		box_box_collision_resolution(t_shape *shape1, t_shape *shape2,
				t_shape *transformed_shape);
void		resolve_sphere_sphere(t_shape *shape1, t_shape *shape2,
				t_shape *transformed_shape);
void		sphere_sphere_collision_resolution(t_shape *sphere1,
				t_shape *sphere2);
bool		box_cylinder_collision(t_shape *box, t_shape *cylinder);
bool		box_plane_collision(t_shape *box, const t_shape *plane,
				bool resolve);

#endif
