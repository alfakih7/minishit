/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 06:22:08 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/19 22:25:06 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	size_t	len;

	i = 0;
	n = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (dst[i] && i < dstsize)
		i++;
	while (src[n] && i + 1 < dstsize)
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	if (i != dstsize)
		dst[i] = '\0';
	return (i + len - n);
}
