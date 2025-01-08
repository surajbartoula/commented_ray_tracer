/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:02:53 by sbartoul          #+#    #+#             */
/*   Updated: 2024/12/26 13:08:36 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "miniRT.h"

double	min(double a, double b);
double	max(double a, double b);
double	max_with_three(double n1, double n2, double n3);
double	min_with_three(double n1, double n2, double n3);
void	add_colors(t_color *res, const t_color *c1, const t_color *c2);
void	mult_color(t_color *res, const t_color *color, double val);
void	sub_colors(t_color *res, const t_color *c1, const t_color *c2);
int		get_color(t_thread_data *tdata, int x, int y);
void	set_color(t_thread_data *tdata, int x, int y, int color);
char	*ftoa(double num);
char	*ft_strjoin_free(char *s1, char *s2, int fre);
#endif
