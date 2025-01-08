/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:27:02 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:27:03 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static int	atof_split(char c)
{
	char	*s;
	int		i;

	s = malloc (sizeof(char) * 2);
	s[0] = c;
	s[1] = '\0';
	i = ft_atoi(s);
	free(s);
	return (i);
}

static void	handle_error(const char *p, bool *status)
{
	if (*p != '\0' && !ft_isdigit(*p) && !is_whitespace(*p))
		*status = false;
}

double	ft_atof(const char *p, bool *status)
{
	double	j;
	double	y;
	int		sign;
	int		v;

	j = 0;
	y = 0;
	v = 1;
	if (p[0] == '.' && p[1] == '\0')
		*status = false;
	sign = 1;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			sign = -1;
		p++;
	}
	while (*p != '.' && ft_isdigit(*p))
		j = j * 10.0 + atof_split(*p++);
	if (*p == '.')
		p++;
	while (*p != '\0' && ft_isdigit(*p))
		y = y + atof_split(*p++) / pow(10.0, v++);
	handle_error(p, status);
	return (sign * (j + y));
}

double	ft_atol(char *str, bool *status)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*status = true;
	while (is_whitespace(str[i]))
		i++;
	if (ft_strcmp(&str[i], "-9223372036854775808") == 0)
		return (LONG_MIN);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (atol_helper(str, i, status) * sign);
}
