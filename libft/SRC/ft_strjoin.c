/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:10:52 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/12 12:01:19 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	counter;
	char	*d;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	counter = (ft_strlen(s1) + ft_strlen(s2));
	d = (char *)malloc((counter + 1) * sizeof (char));
	if (!d)
		return (NULL);
	counter = 0;
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[counter])
		d[i++] = s2[counter++];
	d[i] = '\0';
	// free (s1);
	return (d);
}
