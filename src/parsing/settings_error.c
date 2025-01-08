/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:06 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:07 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	check_colons(char *line)
{
	int	colon_count;
	int	i;

	colon_count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ':')
			colon_count++;
		i++;
	}
	if (colon_count != 1)
	{
		printf(INVALID_PROPERTY, line);
		return (false);
	}
	return (true);
}

bool	check_braces(char *settings_str, size_t *line_num)
{
	int	opening;
	int	closing;
	int	i;

	opening = 0;
	closing = 0;
	i = -1;
	while (settings_str[++i])
	{
		if (settings_str[i] == '{')
			opening++;
		if (settings_str[i] == '}')
			closing++;
	}
	if (opening > 1 || closing > 1 || settings_str[i - 1] != '}')
	{
		if (opening > 1)
			printf(EXTRA_OPENING_BRACE, *line_num);
		if (closing > 1)
			printf(EXTRA_CLOSING_BRACE, *line_num);
		if (settings_str[i - 1] != '}')
			printf(INVALID_TERMINATION, *line_num);
	}
	return (opening == 1 && closing == 1 && settings_str[i - 1] == '}');
}

char	*check_settings_str(char *settings_str, size_t *line_num)
{
	if (ft_strnstr(settings_str, "}", ft_strlen(settings_str)) == NULL
		|| ft_strlen(settings_str) == 2
		|| !check_braces(settings_str, line_num))
	{
		if (ft_strnstr(settings_str, "}", ft_strlen(settings_str)) == NULL)
			printf(UNTERMINATED_SETTINGS, *line_num);
		if (ft_strlen(settings_str) == 2)
			printf(EMPTY_SETTINGS, *line_num);
		free(settings_str);
		return (NULL);
	}
	return (settings_str);
}
