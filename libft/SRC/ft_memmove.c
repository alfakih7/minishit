/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 04:12:38 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/13 14:20:49 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if ((char *)dst >= (char *)src)
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((const char *)src)[len - 1];
			len--;
		}
		return (dst);
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
		return (dst);
	}
}
