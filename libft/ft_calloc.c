/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oallan <oallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:57:08 by oallan            #+#    #+#             */
/*   Updated: 2024/07/31 15:57:26 by oallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	tmp = malloc(size * count);
	if (!tmp)
		return (NULL);
	return (ft_memset(tmp, 0, size * count));
}
