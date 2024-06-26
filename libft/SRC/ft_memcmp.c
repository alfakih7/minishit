/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:48:59 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/13 14:20:26 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < (n - 1) && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	return (0);
}
