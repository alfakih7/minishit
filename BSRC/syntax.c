/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:14 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/02 15:24:41 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_redirection(char *line, int i)
{
	if (!line[++i])
		return (false);
	if (line[i] == '>' || line[i] == '|')
		i++;
	while (line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '<' || line[i] == '>' || line[i] == '|')
		return (false);
	return (true); /////////chack quote
}

bool	check_syntax(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == '>')
				check_redirection(line, i);
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
