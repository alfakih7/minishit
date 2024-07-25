/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:30:00 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/24 03:19:28 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(char **env)
{
	char	**split_path;
	char	*tmp;
	int		i;

	i = 0;
	if (!env || !env[i])
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	split_path = ft_split((env[i] + 5), ':');
	i = -1;
	while (split_path[++i])
	{
		tmp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		free(tmp);
	}
	return (split_path);
}
