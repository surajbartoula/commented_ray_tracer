/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:08:28 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 13:08:31 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# include <stddef.h>
# include <stdbool.h>
# include "miniRT.h"
# include <math.h>

# define RED "\033[31m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"
# define MAGENTA "\e[0;35m"
# define GREEN "\033[32m"
# define LIGHT_MAX 20
# define SHAPE_MAX 100

# define GENERIC_ERROR "\033[33mError with parsing %s on \
line #%d\n\n\033[31m->\t%s\n\n"

# define ORIENT_X_OOR "\033[33mThe x value is out of range \
[-1.0 -> 1.0]\n\033[0m"

# define ORIENT_Y_OOR "\033[33mThe y value is out of range \
[-1.0 -> 1.0]\n\033[0m"

# define ORIENT_Z_OOR "\033[33mThe z value is out of range \
[-1.0 -> 1.0]\n\033[0m"

# define ORIENT_ZERO "\033[33mThe orientation vector cannot be the \
zero vector\n\033[0m"

# define RED_ERR "\033[33mThe red value is out of range \
[0 -> 255]\n\033[0m"

# define GREEN_ERR "\033[33mThe green value is out of range \
[0 -> 255]\n\033[0m"

# define BLUE_ERR "\033[33mThe blue value is out of range \
[0 -> 255]\n\033[0m"

# define MULTI_ELEMENT_ERROR "\033[31mError: Scene contains multiple \
%s\n\033[0m"

# define NO_ELEMENT_ERROR "\033[31mError: Scene contains no \
%s\n\033[0m"

# define MAX_ELEMENT_ERROR "\033[31mError: Scene contains more than \
%d %s\n\033[0m"

# define UNKNOWN_IDENTIFIER "\033[33mUnknown identifier \"%s\" on \
line #%d\n\033[31m->\t%s\n\033[0m"

# define LIGHT_INTENSITY_OOR "\033[33m%s intensity value is out of range on \
line #%d\n\n\033[31m->\t%s\n\n\033[0m"

# define CAMERA_UP_VECTOR "\033[33mCamera orientation cannot be the up vector \
(0, 1, 0)\n\033[0m"

# define CAMERA_FOV_OOR "\033[33mThe fov value is out of range \
[1 -> 180]\n\033[0m"

# define POSITIVE_VALUE "\033[33m%s has to be a positive number on line \
#%d\n\n\033[31m->\t%s\n\n\033[0m"

# define LIGHT_SYNTAX "\033[33mCorrect syntax is \"L [origin] [intensity] \
[color]\"\n\033[0m"

# define AMBIENT_LIGHT_SYNTAX "\033[33mCorrect syntax is \"A [intensity] \
[color]\"\n\033[0m"

# define CAMERA_SYNTAX "\033[33mCorrect syntax is \"C [origin] [orientation] \
[fov]\"\n\033[0m"

# define SPHERE_SYNTAX "\033[33mCorrect syntax is \"sp [origin] [diameter] \
[color]\"\n\033[0m"

# define PLANE_SYNTAX "\033[33mCorrect syntax is \"pl [origin] [orientation] \
[color]\"\n\033[0m"

# define CYLINDER_SYNTAX "\033[33mCorrect syntax is \"cy [origin] \
[orientation] [diameter] [height] [color]\"\n\033[0m"

# define CONE_SYNTAX "\033[33mCorrect syntax is \"co [origin] [orientation] \
[diameter] [height] [color]\"\n\033[0m"

# define CUBE_SYNTAX "\033[33mCorrect syntax is \"cu [origin] [side length] \
[color]\"\n\033[0m"

# define SPOTLIGHT_SYNTAX "\033[33mCorrect syntax is \"SL [origin] [intensity] \
[orientation] [beam width] [color]\"\n\033[0m"

# define SPOTLIGHT_ANGLE_OOR "\033[33mThe spotlight beam width value is out \
of range [1 -> 180] on line #%d\n\n\033[31m->\t%s\n\n\033[0m"

# define SETTINGS_NO_SHAPE "\033[31mSettings at line %ld do not belong to any \
shape\n\033[0m"

# define UNTERMINATED_SETTINGS "\033[31mUnterminated shape settings starting \
at line %ld\n\033[0m"

# define EMPTY_SETTINGS "\033[31mEmpty shape settings starting at line \
%ld\n\033[0m"

# define EXTRA_OPENING_BRACE "\033[31mShape settings starting at line %ld \
contains an extra opening brace\n\033[0m"

# define EXTRA_CLOSING_BRACE "\033[31mShape settings starting at line %ld \
contains an extra closing brace\n\033[0m"

# define INVALID_TERMINATION "\033[31mShape settings starting at line %ld is \
not terminated correctly\n\033[0m"

# define INVALID_PROPERTY "\033[33mError with parsing this property \
\n\033[31m->\t%s\n\033[33mCorrect syntax is KEY : VALUE\n\033[0m"

# define INVALID_KEY "\033[33mError with parsing this property\n\033 \
[31m->\t%s\n\033[33m`%s` is not a valid key\n\033[0m"

# define COLOR_SETTING_ERROR "\033[33mError with parsing this property\n\033 \
[31m->\t%s : %s\n\033[33m`%s` is not a valid value\n\e[0;35mAvailable colors \
are BLUE, RED, PURPLE, GREEN, YELLOW, PINK, BLACK, GRAY\n\033[0m"

# define INVALID_PROP_VALUE "\033[33mError with parsing this property\n \
\033[31m->\t%s : %s\n\033[33m`%s` is not a valid value\n\033[0m"

# define INVALID_PROPERTY_RANGE "\033[33mError with parsing this property \
\n\033[31m->\t%s : %s\n\033[33m%s has to be between %.2f and %.2f\n\033[0m"

#endif
