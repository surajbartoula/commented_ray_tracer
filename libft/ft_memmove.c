/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oallan <oallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:00:43 by oallan            #+#    #+#             */
/*   Updated: 2024/07/31 16:00:44 by oallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst - src > 0)
	{
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		return ((void *)dst);
	}
	return (ft_memcpy(dst, src, len));
}
