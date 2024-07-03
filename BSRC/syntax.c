/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:14 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/04 02:33:27 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool	check_pipe(char *line, int i)
{
	int	j;

	j = 0;
	i++;
	while (line[i] && j <= i)
	{
		if (line[j] != ' ')
			break;
		j++;
	}
	if (j == i)
		return (false);
	while (line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n' || line[i] == '|')
		return (false);
	return (true);
}

static bool	check_redirection(char *line, int i)
{
	char	redirection_type;

	redirection_type = line[i];
	if (line[++i] == '\0')
		return (false);
	if (redirection_type == '>')
	{
		if (line[i] == '>')
			i++;
	}
	else
	{
		if (line[i] == '<')
			i++;
	}
	while (line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n' || line[i] == '<' || line[i] == '>' || line[i] == '|')
		return (false);
	return (true);
}

bool	check_syntax(char *line)
{
	int	i;
	int	if_quotes;

	i = 0;
	if_quotes = 0;
	if (line)
	{
		while (line[i])
		{
			if (!if_quotes && line[i] == '\'')
				(i++, if_quotes = 1);
			if (!if_quotes && line[i] == '\"')
				(i++, if_quotes = 2);
			if ((if_quotes == 1 && line[i] == '\''))
				(i++, if_quotes = 0);
			if ((if_quotes == 2 && line[i] == '\"'))
				(i++, if_quotes = 0);
			if (!if_quotes && (line[i] == '>' || line[i] =='<'))
			{
				if (!check_redirection(line, i))
					return (false);
			}
			else if (!if_quotes && line[i] == '|')
			{
				if (!check_pipe(line, i))
					return (false);
			}
			i++;
		}
	}
	return (true);
}
