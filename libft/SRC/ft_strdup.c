/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:43:02 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 21:15:18 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	n;
	char	*dup;

	i = 0;
	if (!s1)
		return (NULL);
	n = ft_strlen(s1);
	dup = (char *)malloc((n + 1) * sizeof (char));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
