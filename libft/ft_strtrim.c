/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oallan <oallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:05:10 by oallan            #+#    #+#             */
/*   Updated: 2024/07/31 16:10:00 by oallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/libft.h"

static int	ft_matchset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_trimmer(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*trimmed;

	i = 0;
	while (s1[i] && ft_matchset(s1[i], set))
		i++;
	j = 0;
	while (s1[i + j])
		j++;
	while (j && ft_matchset(s1[i + (j - 1)], set))
		j--;
	trimmed = ft_calloc(j + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (j && j--)
		trimmed[j] = s1[i + j];
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (!s1)
		return (NULL);
	if (!set)
		return (NULL);
	return (ft_trimmer(s1, set));
}
