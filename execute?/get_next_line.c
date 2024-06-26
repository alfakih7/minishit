/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:13:34 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/03 07:34:28 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_read_line(int fd, char *rem)
{
	char	*buffer;
	int		n;

	n = 1;
	buffer = (char *)malloc(2);
	if (!buffer)
		return (NULL);
	while (n > 0 && !get_ft_strchr(rem, '\n'))
	{
		n = read(fd, buffer, 1);
		if (n < 0 || !buffer)
			return (free(buffer), free(rem), rem = NULL, NULL);
		buffer[n] = '\0';
		rem = get_ft_strjoin(rem, buffer);
	}
	if ((n == 0 && (rem && !(rem[0]))))
		return (free(buffer), free(rem), rem = NULL, NULL);
	free(buffer);
	buffer = NULL;
	return (rem);
}

char	*get_next_line(int fd)
{
	char		*line;

	line = NULL;
	if (fd < 0 || 1 <= 0 || 1 >= INT_MAX)
		return (NULL);
	line = ft_read_line(fd, line);
	if (!line || (!line[0]))
		return (free(line), line = NULL, NULL);
	return (line);
}
