# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 20:54:22 by sbartoul          #+#    #+#              #
#    Updated: 2025/01/04 13:24:24 by sbartoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

MLX_PATH = mlx/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_PATH = libft/

LIBFT_LIB = $(LIBFT_PATH)libft.a

GETNEXTLINE := get_next_line/get_next_line_utils.c \
			get_next_line/get_next_line.c \

SRC_DIR = src/renderer/init_display.c \
		src/renderer/transform.c \
		src/renderer/render_shape.c \
		src/renderer/init_setting.c \
		src/renderer/draw.c \
		src/renderer/orientation.c \
		src/renderer/fill_pixels.c \
		src/renderer/super_sample.c \
		src/renderer/projection.c \
		src/renderer/render_scene.c \
		src/renderer/camera.c \
		src/renderer/threads.c \
		src/renderer/marker.c \
		src/parsing/utils2.c \
		src/parsing/texture2.c \
		src/parsing/shape2.c \
		src/parsing/shape_errors.c \
		src/parsing/settings2.c \
		src/parsing/utils1.c \
		src/parsing/scene.c \
		src/parsing/texture1.c \
		src/parsing/settings1.c \
		src/parsing/shape1.c \
		src/parsing/spotlight.c \
		src/parsing/utils4.c \
		src/parsing/elements1.c \
		src/parsing/attributes2.c \
		src/parsing/settings_error.c \
		src/parsing/error.c \
		src/parsing/settings_validation2.c \
		src/parsing/elements2.c \
		src/parsing/attribute_errors.c \
		src/parsing/utils3.c \
		src/parsing/element_errors.c \
		src/parsing/attributes1.c \
		src/parsing/settings_validation1.c \
		src/parsing/settings3.c \
		src/parsing/error_utils.c \
		src/shading/cube_mapping.c \
		src/shading/reflection.c \
		src/shading/shape_texture.c \
		src/shading/utils.c \
		src/shading/modification2.c \
		src/shading/patterns.c \
		src/shading/transformations.c \
		src/shading/modification1.c \
		src/shading/matrix.c \
		src/shading/mapping_utils.c \
		src/linear_algebra/inverse_matrix.c \
		src/linear_algebra/matrix_transformation.c \
		src/linear_algebra/matrix_operation.c \
		src/linear_algebra/vector_arithmetic.c \
		src/linear_algebra/determinant_matrix.c \
		src/linear_algebra/detmat.c \
		src/linear_algebra/vector_operation.c \
		src/interaction/setup_hooks.c \
		src/interaction/mouse.c \
		src/interaction/hook_rotate.c \
		src/interaction/ray_intersection.c \
		src/interaction/toggle_key.c \
		src/interaction/lookat_animation.c \
		src/interaction/hook_move.c \
		src/interaction/scale_change.c \
		src/interaction/toggle_shape.c \
		src/interaction/key_press.c \
		src/interaction/loop_hook_transform.c \
		src/interaction/lookat.c \
		src/interaction/free_textures.c \
		src/interaction/camera_controls.c \
		src/interaction/free_utils.c \
		src/interaction/mouse_utils.c \
		src/interaction/lights.c \
		src/interaction/shape.c \
		src/interaction/loop_hook.c \
		src/intersections/cylinder_intersection.c \
		src/intersections/intersections.c \
		src/intersections/normal_map.c \
		src/intersections/normal.c \
		src/intersections/texture.c \
		src/intersections/cone_intersections.c \
		src/collision/fill_vtx1.c \
		src/collision/intersection_compute.c \
		src/collision/check_collision.c \
		src/collision/cylinderplane_collision.c \
		src/collision/closest_point_on_box.c \
		src/collision/sphere_box_collision.c \
		src/collision/cy_p_collision_res.c \
		src/collision/fill_vtx2.c \
		src/collision/glk_support.c \
		src/collision/gjk.c \
		src/collision/sameshape_collision.c \
		src/collision/on_origin.c \
		src/collision/secondary_plane.c \
		src/collision/test_box_overlap.c \
		src/collision/collision.c \
		src/collision/tetrahedron_on_origin.c \
		src/collision/triangle_on_origin.c \
		src/collision/cylinder_sphere_collision.c \
		src/collision/test_box_axes.c \
		src/collision/collision_resolution.c \
		src/collision/box_collision.c \
		src/math/color_getter_setter.c \
		src/math/color_utils.c \
		src/math/colors_math.c \
		src/math/min_max.c \
		src/main.c \

CFILES = $(SRC_DIR)

OBJECTS = $(CFILES:%.c=%.o)

all: subsystems $(NAME)

%.o : %.c 
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -Imlx -c -o $@ $<

subsystems:
	@echo $(B)
	make -C $(MLX_PATH) all
	@echo $(B)
	make -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	@echo $(Y)Compiling [$(CFILES)]...$(X)
	@echo $(G)Finished [$(CFILES)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(MLX_LIB) $(LIBFT_LIB) $(GETNEXTLINE) -o $(NAME)
	@echo $(G)Ready [$(NAME)]$(X)

clean:
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJECTS)
	@echo $(R)Removed [$(OBJECTS)]$(X)

fclean: clean
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

.PHONY: all clean fclean re
