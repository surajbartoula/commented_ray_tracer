/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:15:09 by sbartoul          #+#    #+#             */
/*   Updated: 2025/01/08 18:40:11 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include <stdbool.h>
# include "miniRT.h"
# include "render.h"

typedef struct s_ray			t_ray;
struct s_ray
{
	t_vector	origin;
	t_vector	dir;
};

//p = o + t.D
typedef struct s_intersect		t_intersection;
struct s_intersect
{//
	double		time; //t along the ray at which the intersection occurs. Smaller t means the intersection is closer to the ray's origin.
	t_shape		*shape;
	t_vector	point;
	t_vector	normal; //The normal vector at the intersection point on the surface of the shape
	t_vector	eye;
	t_vector	over_point; //A small offset of the intersection point along the normal direction
	t_vector	reflect_vec; //reflected vector calculated at the intersection point. reflect_vec = D - 2.(D.N).N. D is incident direction vector and N is surface normal
	bool		inside; //Indicates whether the intersection occurs inside the shape
};

typedef struct s_intersections	t_intersections;
struct s_intersections
{
	t_intersection	arr[200];
	int				count;
};

void			calculate_specular(t_vector *reflect_v, t_intersection *itx,
					t_glear *glear, t_light *light);
t_color			ring_pattern(t_intersection *itx, t_vector point, t_color a,
					t_color b);
t_color			gradient_pattern(t_intersection *itx, t_vector point, t_color a,
					t_color b);
t_color			checker_pattern(t_intersection *itx, t_vector *point);
t_color			stripe_pattern(t_intersection *itx, t_vector point,
					t_color a, t_color b);
t_color			get_shape_color(t_intersection *itx);
t_color			get_texture_color(t_intersection *p);
t_color			cast_reflection_ray(t_scene *scene,
					t_intersection *intersection, int remaining, int light_idx);
t_color			glear(t_intersection *itx, t_scene *scene, int light_idx);
t_color			reflection_color(t_intersection *itx, t_scene *scene,
					int remaining, int light_idx);
bool			intersect(t_shape *shape, const t_ray *ray,
					t_intersections *xs);
t_intersection	*hit(t_intersections *xs);
t_vector		get_texture_coords(const t_shape *shape, double u, double v,
					t_vector *normal);
t_vector		sphere_normal(t_vector *normal, const t_shape *shape,
					const t_vector *itx_point);
t_vector		cube_normal(const t_shape *shape, const t_vector *itx_point);
t_vector		plane_normal(const t_shape *shape, const t_vector *itx_point);
t_vector		cone_normal(const t_shape *shape, const t_vector *itx_point);
t_vector		cylinder_normal(const t_shape *shape,
					const t_vector *itx_point);
t_vector		normal_map(t_vector *normal, const t_shape *shape,
					const t_vector *itx_point);
t_vector		normal_at(const t_shape *shape, const t_vector *itx_point);
void			prepare_computations(t_intersection *intersection,
					t_ray *ray);
bool			get_specular_and_diffuse(t_scene *scene, int light_idx,
					t_intersection *itx, t_glear *phong);
t_color			super_sample_pixel(double x, double y, t_intersections *arr,
					t_thread_data *tdata);
void			cylindrical_map(double *u, double *v, t_vector *point);
void			spherical_map(double *u, double *v, t_vector *point);
void			ray_position(t_vector *pos, const t_ray *ray, double time);
bool			intersect_cylinder(const t_ray *ray, t_shape *shape,
					t_intersections *xs);
bool			intersect_plane_fast(const t_ray *ray, t_shape *plane,
					t_intersections *xs);
bool			intersect_cube(t_shape *shape, t_ray *ray, t_intersections *xs);
bool			intersect_sphere_fast(const t_ray *ray, t_intersections *xs,
					t_shape *sphere);
bool			intersect_cone(const t_ray *ray, t_shape *shape,
					t_intersections *xs);
void			ft_swapd(double *a, double *b);

#endif