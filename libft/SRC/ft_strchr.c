/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:52:03 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/10 08:33:24 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	x;

	x = c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != x)
		i++;
	if (s[i] == '\0' && x != 0)
		return (NULL);
	return ((char *)&s[i]);
}
