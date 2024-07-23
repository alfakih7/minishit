/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:03:07 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/21 17:04:20 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int ft_inside_quotes(t_inside *inside , int c){
	if(c == '\'' && !inside->dquotes){
        inside->quotes = !inside->quotes;
    }else if(c == '\"' && !inside->quotes){
			inside->dquotes = !inside->dquotes;
		}
		return (1);
}
static int	is_special(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char *joined_str(char *line)
{
	char	*result;
	int		size;
	int		i;
	int		n; /// name it better
	char	c;
	t_inside inside;

	inside.dquotes = 0;
	inside.quotes = 0;
	i = 0;
	size = ft_strlen(line);
	while(line[i])
	{
		c = line[i];
		ft_inside_quotes(&inside , c);
		if (is_special(c) && !inside.dquotes && !inside.quotes)
		{
			size++;
			i++;
			if (is_special(line[i]))
				i++;
		}
		else
			i++;
	}
	result = malloc(size + 1);
	i = 0;
	n = 0;
	while (line[i])
	{
		c = line[i];
		ft_inside_quotes(&inside , c);
		if (is_special(c) && !inside.dquotes && !inside.quotes)
		{
			result[n++] = ' ';
			result[n++] = line[i++];
			if (is_special(line[i]))
				result[n++] = line[i++];
		}
		else
			result[n++] = line[i++];
	}
	result[n] = '\0';
	return (result);
}