/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:55:59 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/29 16:36:12 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include "libft.h"
# include "shape.h"
# include "color.h"
# include "lights.h"
# include <stdio.h>
# include "display.h"
# include "scene.h"
# include "parsing.h"
# include "parsing2.h"
# include "interactions.h"
# include "../../mlx/mlx.h"
# include "display.h"
# include "display.h"
# include "camera.h"
# include "intersection.h"
# include "render.h"
# include "math_utils.h"
# include "collision.h"
# include "macro.h"
# include "mathRT.h"
# define EPSILON 0.001f

#endif