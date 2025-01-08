/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:04:04 by sbartoul          #+#    #+#             */
/*   Updated: 2024/03/25 23:41:48 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlength(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	slen;
	size_t	i;

	slen = ft_strlength(str) + 1;
	ptr = malloc(sizeof(char) * slen);
	if (!ptr)
		return (0);
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr;
	int		len;

	if (!s1 && !s2)
		return (0);
	len = ft_strlength(s1) + ft_strlength(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ptr = str;
	if (s1)
		while (*s1)
			*ptr++ = *s1++;
	if (s2)
		while (*s2)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (0);
	while (*str != (char)c)
		if (!*str++)
			return (0);
	return ((char *)str);
}
