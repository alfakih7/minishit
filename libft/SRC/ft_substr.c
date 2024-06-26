/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:49:00 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/17 13:59:50 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allo(size_t start, size_t i, size_t len, const char *s)
{
	size_t	counter;
	char	*d;

	counter = 0;
	while (i < (start + len) && s[i])
	{
		i++;
		counter++;
	}
	d = (char *)malloc((counter + 1) * sizeof (char));
	if (!d)
		return (NULL);
	return (d);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	z;
	char	*d;

	if (!s)
		return (NULL);
	i = start;
	z = ft_strlen(s);
	if (start >= z)
	{
		d = (char *)malloc(sizeof (char));
		if (!d)
			return (NULL);
		d[0] = '\0';
		return (d);
	}
	d = ft_allo(start, i, len, s);
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		d[i++] = s[start++];
	d[i] = '\0';
	return (d);
}
