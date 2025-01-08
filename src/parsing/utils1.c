/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:54 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:55 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	is_whitespace(const char c)
{
	return (c == ' ' || c == '\f'
		|| c == '\n' || c == '\r'
		|| c == '\t' || c == '\v');
}

bool	all_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

size_t	count_commas(const char *str)
{
	size_t	i;
	size_t	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	return (comma_count);
}

bool	is_num(const char *str, bool decimal)
{
	size_t	i;
	size_t	dot_count;

	i = 0;
	dot_count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+'
			&& str[i] != '.')
			return (false);
		if (str[i] == '.')
			dot_count++;
		if ((str[i] == '-' || str[i] == '+') && i != 0)
			return (false);
		i++;
	}
	if (dot_count > 1 || (dot_count > 0 && decimal == false))
		return (false);
	if ((str[0] == '-' || str[0] == '+') && ft_strlen(str) == 1)
		return (false);
	if ((str[0] == '-' || str[0] == '+') && str[1] == '.'
		&& ft_strlen(str) == 2)
		return (false);
	return (true);
}

size_t	split_count(char **split)
{
	size_t	len;

	if (split == NULL)
		return (0);
	len = 0;
	while (split[len] != NULL)
		len++;
	return (len);
}
