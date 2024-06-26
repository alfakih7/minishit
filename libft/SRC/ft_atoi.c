/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:51:37 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/13 14:16:44 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	result(const char *str, size_t i, size_t x, int n)
{
	unsigned long long	k;
	unsigned long long	tmp;

	tmp = 0;
	k = 0;
	while (str[i] >= '0' && str[i] <= 57 && str[i] && k < 9223372036854775807)
	{
		tmp = k;
		k = k * 10 + str[i++] - '0';
		if (k < tmp || ((i - x) > 19))
		{
			if (n == 1)
				return (-1);
			return (0);
		}
	}
	if (k > 9223372036854775807 && n == 1)
		return (-1);
	if (k > 9223372036854775807 && n == -1)
		return (0);
	return (k);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	x;
	int		n;

	x = 0;
	i = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
		x++;
	}
	while (str[i] == '0' && str[i])
	{
		i++;
		x++;
	}
	return (n * result(str, i, x, n));
}
