/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:03:07 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/10 20:02:02 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>
#include <stdlib.h>

static int ft_inside_quotes(t_inside *inside , int c){
	if(c == '\'' && !inside->dquotes){
        inside->quotes = !inside->quotes;
    }else if(c == '"' && !inside->quotes){
			inside->dquotes = !inside->dquotes;
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
	t_inside *inside;

	inside = malloc(sizeof (t_inside));
	inside->dquotes = 0;
	inside->quotes = 0;

	i = 0;
	size = ft_strlen(line);
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
		ft_inside_quotes(inside , c);
		{
		if (is_special(c) && !(inside->dquotes || inside->quotes))
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
