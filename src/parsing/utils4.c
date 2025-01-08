/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:27:06 by allan             #+#    #+#             */
/*   Updated: 2025/01/04 11:27:07 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

long	atol_helper(char *str, int i, bool *status)
{
	long	tem;
	long	n;

	n = 0;
	tem = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tem = n;
		n *= 10;
		n += str[i++] - '0';
		if (n < tem)
			return ((*status = false), 0);
	}
	return (n);
}

static char	*dec_num(int is_negative, int len, int decimal, char *str)
{
	int	i;

	i = 0;
	if (is_negative)
		str[0] = '-';
	if (decimal == 0)
		len = 1;
	i = len - 1 + is_negative;
	while (i >= is_negative)
	{
		str[i] = (decimal % 10) + '0';
		decimal /= 10;
		i--;
	}
	return (str);
}

static char	*point_num(double num, int start, int len, char *str)
{
	int	decimal;
	int	i;

	decimal = 0;
	len = ft_strlen(str);
	str[len] = '.';
	num = num - (double)decimal;
	num = num - (double)start;
	num = fabs(num) * 100;
	decimal = (int)num;
	i = 1;
	while (i >= 0)
	{
		str[i + len + 1] = (decimal % 10) + '0';
		decimal /= 10;
		i--;
	}
	return (str);
}

char	*ftoa(double num)
{
	char	*str;
	int		i[3];
	int		decimal[2];

	i[2] = 0;
	if (num < 0)
	{
		i[2] = 1;
		num = -num;
	}
	decimal[0] = (int)num;
	decimal[1] = (int)num;
	i[1] = 0;
	i[0] = decimal[0];
	while (i[0] != 0)
	{
		i[0] /= 10;
		i[1]++;
	}
	str = (char *)ft_calloc(i[1] + 20, sizeof(char));
	dec_num(i[2], i[1], decimal[0], str);
	point_num(num, decimal[1], i[1], str);
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2, int fre)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = ft_strjoin(s1, s2);
	if (fre == 1 || fre == 3)
		free(s1);
	if (fre == 2 || fre == 3)
		free(s2);
	return (str);
}
