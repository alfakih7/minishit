/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:03:07 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/13 15:45:59 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>

#include <string.h>
#include <stdlib.h>

int ft_inside_quotes(t_inside *inside , int c){
	if(c == '\'' && !inside->dquotes){
        inside->quotes = !inside->quotes;
    }else if(c == '\"' && !inside->quotes){
			inside->dquotes = !inside->quotes;
		}
		return (1);
}

static int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
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

	i = 0;
	size = strlen(line);
	while(line[i])
	{
		c = line[i];
		if (is_special(c))
			size++;
		while(is_special(line[i]))
			i++;
		i++;
	}
	result = malloc(size + 1);
	i = 0;
	n = 0;
	while (line[i])
	{
		c = line[i];
		if (is_special(c) && (ft_inside_quotes == 1)) /////this not working
		{
			result[n++] = ' ';
			c = line[i];
			if (is_special(c))
				result[n++] = line[i++];
		}
		result[n++] = line[i++];
	}
	result[n] = '\0';
	return (result);
}
