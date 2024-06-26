/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:12:14 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/17 14:46:11 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	x;

	x = 0;
	if (!dst && !src)
		return (NULL);
	while (x < n)
	{
		((char *)dst)[x] = ((const char *)src)[x];
		x++;
	}
	return (dst);
}
