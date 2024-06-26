/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 07:16:20 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/01/17 13:57:51 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char	**d, size_t j)
{
	size_t	start;

	start = 0;
	if (!d[j])
	{
		while (start <= j)
			free (d[start++]);
		free (d);
		return (0);
	}
	return (1);
}

static char	**ft_ballo(char const *s, char c)
{
	size_t	x;
	int		counter;
	char	**d;

	x = 0;
	counter = 0;
	while (s[x])
	{
		while (s[x] == c && s[x])
			x++;
		if (s[x] != c && s[x] != '\0')
		{
			counter++;
			while (s[x] != c && s[x])
				x++;
		}
	}
	d = (char **)malloc((counter +1) * sizeof(char *));
	if (!d)
	{
		free (d);
		return (NULL);
	}
	return (d);
}

static char	**ft_check(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_ballo(s, c));
}

static char	*ft_smallo(char const *s, char c, size_t start)
{
	size_t	counter;
	char	*d;

	counter = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		counter++;
	}
	d = (char *)malloc((counter + 1) * sizeof(char));
	if (!d)
		return (NULL);
	return (d);
}

char	**ft_split(char const *s, char c)
{
	t_split	z;

	z.i = 0;
	z.j = 0;
	z.start = 0;
	z.d = ft_check(s, c);
	if (!z.d)
		return (NULL);
	while (s[z.i])
	{
		if (s[z.i] != c)
		{
			z.d[z.j] = ft_smallo(s, c, z.i);
			z.start = 0;
			if (ft_free(z.d, z.j) == 0)
				return (NULL);
			while (s[z.i] != c && s[z.i])
				z.d[z.j][z.start++] = s[z.i++];
			z.d[z.j++][z.start] = '\0';
		}
		while (s[z.i] == c && s[z.i])
			z.i++;
	}
	z.d[z.j] = NULL;
	return (z.d);
}
