/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:28:14 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/13 14:22:52 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	x;

	x = c;
	i = 0;
	while (s[i])
	{
		i++;
	}
	if (x == 0)
	{
		return ((char *)&s[i]);
	}
	while (i > 0 && s[i - 1] != x)
		i--;
	if (i == 0)
	{
		return (NULL);
	}
	return ((char *)&s[i - 1]);
}
