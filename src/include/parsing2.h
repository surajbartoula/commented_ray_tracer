/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:15:28 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/28 23:34:40 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING2_H
# define PARSING2_H

# include "miniRT.h"

double		ft_atol(char *str, bool *status);
long		atol_helper(char *str, int i, bool *status);
double		ft_atof(const char *p, bool *status);
bool		print_color_error(t_color_err *err, const char *line, int line_num,
				char *element);
bool		print_orient_error(t_orient_err *err, const char *line,
				int line_num, char *element);
void		parse_orientation(t_vector *orientation, const char *str,
				t_orient_err *err);
void		check_color_range(t_color *color, t_color_err *err);
void		parse_color(t_color *color, const char *str, t_color_err *errs);
void		parse_coordinates(t_vector *position, const char *str,
				bool *status);
void		check_orientation_vector(t_vector *orientation, t_orient_err *err);
bool		print_cam_error(t_cam_err *err, const char *line, int line_num);
void		parse_light_props(t_scene *scene, t_light *light, char **splitted);
void		parse_light(t_scene *scene, char **splitted);
bool		parse_ambient_props(t_scene *scene);
bool		parse_ambient(t_scene *scene, char **splitted);
void		parse_camera(t_scene *scene, char **split);
void		print_error(t_scene *scene, const char *line, int line_num,
				const char *identifer);
bool		check_element_count(t_scene *scene);
bool		skip_line(char **line, int fd, size_t *line_count);
bool		parse_line(t_scene *scene, char *line, size_t *line_num, int fd);
t_scene		*check_elements(t_scene *scene);
t_scene		*parse_scene(int fd);
bool		check_colons(char *line);
bool		check_braces(char *settings_str, size_t *line_num);
char		*check_settings_str(char *settings_str, size_t *line_num);
int			ft_strcmp_case(const char *s1, const char *s2);
bool		is_settings(const char *line);
bool		is_valid_key(const char *key);
bool		is_valid_color(const char *color);
bool		check_value(const char *key, const char *val,
				double min, double max);
bool		is_valid_val(const char *key, const char *val);
char		*get_settings_str(size_t *line_num, int fd, const char *set);
bool		check_key_val_split(char **key_val, char **settings, int line_idx);
bool		check_key_vals(char **key_val, char **settings, t_scene *scene,
				int line_idx);
t_color		parse_color_value(const char *str);
bool		parse_rest_of_settings(t_shape *shape, char **key_val);
bool		parse_setting(t_shape *shape, char **key_val);
bool		parse_split_settings(t_scene *scene, char **settings);
bool		parse_settings(t_scene *scene, const char *settings_start,
				size_t *line_num, int fd);
void		parse_cylinder_props(t_shape *shape, t_scene *scene,
				char **splitted);
void		parse_cylinder(t_scene *scene, t_shape *shape, char **splitted);
void		parse_cone(t_scene *scene, t_shape *shape, char **splitted);
bool		parse_shape(t_scene *scene, char **splitted);
void		init_shape(t_shape *shape, t_scene *scene);
void		parse_sphere(t_scene *scene, t_shape *shape, char **splitted);
void		parse_cube(t_scene *scene, t_shape *shape, char **splitted);
void		parse_plane(t_scene *scene, t_shape *shape, char **splitted);
bool		is_shape(const char *identifier);
void		parse_spotlight_props2(t_light *light, char **splitted,
				t_scene *scene);
void		parse_spotlight_props(t_scene *scene, t_light *light,
				char **splitted);
void		parse_spotlight(t_scene *scene, char **splitted);
int			read_rest_of_header(char *buff, int *w, int *h, int fd);
int			read_ppm_header(int fd, int *w, int *h);
t_color		read_ppm_color(unsigned char *buff, int idx);
t_color		**fill_colors_array(int bytes_read, char *img_path,
				unsigned char *buff, t_shape *shape);
t_color		**parse_texture(char *img_path, t_shape *shape);
bool		is_whitespace(const char c);
bool		all_whitespace(const char *str);
size_t		count_commas(const char *str);
bool		is_num(const char *str, bool decimal);
size_t		split_count(char **split);
void		free_2d_array(char **arr);
char		*ft_strtrim_free(char *s1, char *set);
char		**ft_split_whitespace(char *s);
void		mat4_multiply(t_vector *res, const t_mat4 *mat,
				const t_vector *vec);
void		free_and_update1(char **rgb, t_color *color, t_color_err *errs);
void		free_and_update2(t_vector *position, double *res, char	**coords);

#endif