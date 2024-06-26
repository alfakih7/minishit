/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:49:32 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/13 14:18:53 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_last(int x)
{
	size_t	count;

	count = 1;
	if (x < 0)
	{
		count++;
		x = x * -1;
	}
	while (x >= 10)
	{
		x = x / 10;
		count++;
	}
	return (count);
}

static char	*ft_allo(int x)
{
	size_t	count;
	char	*s;

	count = 1;
	if (x < 0)
	{
		count++;
		x = x * -1;
	}
	while (x >= 10)
	{
		x = x / 10;
		count++;
	}
	s = (char *)malloc((count + 1) * sizeof(char));
	if (!s)
		return (NULL);
	return (s);
}

char	*ft_itoa(int n)
{
	size_t	i;
	int		x;
	char	*rev;

	i = ft_last(n);
	x = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	rev = ft_allo(x);
	if (rev == NULL)
		return (NULL);
	if (x < 0)
		x = x * -1;
	rev[i--] = '\0';
	while (x >= 10)
	{
		rev[i--] = (x % 10) + 48;
		x = x / 10;
	}
	rev[i] = (x % 10) + 48;
	if (n < 0)
		rev[--i] = '-';
	return (rev);
}
