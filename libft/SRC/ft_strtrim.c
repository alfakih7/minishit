/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:20:32 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/17 14:14:34 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_i(const char *s1, const char *set)
{
	size_t	i;
	size_t	check;
	size_t	x;

	i = 0;
	check = 0;
	x = 0;
	while (i == check && s1[i])
	{
		while (set[x])
		{
			if (s1[i] == set[x])
			{
				i++;
				break ;
			}
			x++;
		}
		x = 0;
		check++;
	}
	return (i);
}

static size_t	ft_n(const char *s1, const char *set, size_t i)
{
	size_t	n;
	size_t	x;
	size_t	check;

	n = (ft_strlen(s1) - 1);
	check = n;
	x = 0;
	while (n == check && n > i)
	{
		while (set[x])
		{
			if (s1[n] == set[x])
			{
				n--;
				break ;
			}
			x++;
		}
		x = 0;
		check--;
	}
	return (n);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	n;
	size_t	counter;
	char	*d;

	if (!s1)
		return (NULL);
	if (!*s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	i = ft_i(s1, set);
	n = ft_n(s1, set, i);
	counter = n - i + 1;
	d = (char *)malloc((counter + 1) * sizeof (char));
	if (!d)
		return (NULL);
	counter = 0;
	while (s1[i] && i <= n)
		d[counter++] = s1[i++];
	d[counter] = '\0';
	return (d);
}
