/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oallan <oallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:43 by oallan            #+#    #+#             */
/*   Updated: 2024/07/31 16:01:44 by oallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (!(char)c)
		return ((char *)(s + i));
	else
		return (NULL);
}
