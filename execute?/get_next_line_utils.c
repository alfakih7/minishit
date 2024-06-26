/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/03 06:33:56 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	get_ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_ft_strchr(const char *s, int c)
{
	int	i;

	c = c % 255;
	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\0')
		return (NULL);
	return ((char *)&s[i]);
}

char	*get_ft_strjoin(char *s1, char *s2)
{
	int		i;
	size_t	counter;
	char	*d;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = -1;
	counter = (ft_strlen(s1) + ft_strlen(s2));
	d = (char *)malloc((counter + 1));
	if (!d)
		return (NULL);
	counter = 0;
	while (s1[++i])
		d[i] = s1[i];
	while (s2[counter])
		d[i++] = s2[counter++];
	d[i] = '\0';
	free(s1);
	s1 = NULL;
	return (d);
}

char	*get_ft_strdup(char *s1)
{
	size_t	i;
	size_t	n;
	char	*dup;

	dup = NULL;
	i = 0;
	if (!s1)
		return (NULL);
	n = ft_strlen(s1);
	dup = malloc((n + 1));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = s1[i];
	return (dup);
}
