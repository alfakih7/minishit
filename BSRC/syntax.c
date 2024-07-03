/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:14 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/02 16:37:08 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_redirection(char *line, int i)
{
	char	redirection_type;

	redirection_type = line[i];
	if (!line[++i])
		return (false);
	if (redirection_type == '>')
	{
		if (line[i] == '>' || line[i] == '|')
			i++;
	}
	else
	{
		if (line[i] == '<')
			i++;
	}
	while (line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '<' || line[i] == '>' || line[i] == '|')
		return (false);///  ls >       (not working)
	return (true);
}

bool	check_syntax(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == '>' || line[i] =='<')
			{
				if (!check_redirection(line, i))
					return (false);
			}
			i++;
		}
	}
	return (true);
}

// static bool	contains(char c)
// {
// 	if (c == '|' || c == '>' || c == '<')
// }

// bool	check_multiple_pipes(char *line)
// {
// 	char	**split;
// 	int		i;

// 	i = -1;
// 	if (line)
// 	{
// 		if (line[0] == '|')
// 			return (false);
// 		while (line[++i])
// 		{
// 			if (line[i])
// 		}
// 	}
// }
