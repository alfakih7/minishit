/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 08:45:13 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/13 14:22:46 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	while (haystack[i] && i < (len))
	{
		x = 0;
		while (haystack[i + x] == needle[x] && i + x < len)
		{
			x++;
			if (!needle[x])
			{
				return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	if (needle[0] == '\0')
	{
		return ((char *)&haystack[0]);
	}
	return (NULL);
}
