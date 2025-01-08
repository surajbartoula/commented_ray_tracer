/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:58 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:26:59 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*line;

	line = NULL;
	if (!s1)
		return (free(s1), NULL);
	line = ft_strtrim(s1, set);
	free(s1);
	return (line);
}

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_words(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (is_whitespace(line[i]) == true && line[i])
			i++;
		if (line[i] == '\0')
			break ;
		count++;
		while (is_whitespace(line[i]) == false && line[i])
			i++;
	}
	return (count);
}

char	*create_string(char *line, int start, int end)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (!res)
		return (free(res), NULL);
	ft_strlcpy(res, &line[start], (end - start) + 2);
	return (res);
}

char	**ft_split_whitespace(char *s)
{
	char	**words;
	int		i;
	int		word_start;
	int		word_count;

	words = malloc(sizeof(char *) * (count_words(s) + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		while (is_whitespace(s[i]) == true && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		word_start = i;
		while (is_whitespace(s[i]) == false && s[i] != '\0')
			i++;
		words[word_count] = create_string(s, word_start, i - 1);
		if (words[word_count++] == NULL)
			return (NULL);
	}
	words[word_count] = NULL;
	return (words);
}
