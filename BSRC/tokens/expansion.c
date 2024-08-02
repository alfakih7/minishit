/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:24:23 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/08/02 14:48:36 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	valid_dollar(char *str, int	i)
{
	i++;
	if (!str[i] || str[i] == ' ' || str[i] == '\"'
		|| str[i] == '\'' || str[i] == '$')
		return (0);
	return (1);
}
static int	find_end_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '$' && str [i] != '=')
			i++;
	return (i);
}

static long	envcmp(char *str, char **my_env)
{
	int	i;
	long	n;

	n = 0;
	i = 0;
	while (my_env[n])
	{
		i = 0;
		while (str[i] && my_env[n][i] && str[i] == my_env[n][i])
		{
			if (my_env[n][i] == '=' && str[i] == '=')
				return (free(str), n);
			i++;
		}
		if (my_env[n][i] == '=' && !str[i])
			return (free(str), n);
		n++;
	}
	return (free(str), 9999999999999);
}

static	int	size_of_expansions(char *line, t_expand **temp, char **env)
{
	t_inside	inside;
	char		*str_temp;
	int			i;
	long		asd;
	int			length;
	int			start;
	int			size_total;

	i = 0;
	t_expand *akram;
	akram = *temp;
	size_total = ft_strlen(line);
	inside.dquotes = 0;
	inside.quotes = 0;
	while (line[i])
	{
		ft_inside_quotes(&inside, line[i]);
		if (line[i] =='$' && valid_dollar(line, i) && (!inside.quotes))
		{
			start = i + 1;
			length = find_end_dollar(&line[start]);
			asd = envcmp(ft_substr(line, start,  length), env);
			if (asd != 9999999999999)
			{
				str_temp = ft_getenv(env[asd]);
				expand_lstadd_back(&akram, expand_lstnew(((void *)str_temp)));
				size_total += ft_strlen(str_temp) - (length + 1);
			}
			else
			{
				expand_lstadd_back(&akram, expand_lstnew(NULL));
				size_total -= (length + 1);
			}
		}
		i++;
	}
	*temp = akram;
	return (size_total);
}

char	*expansion(char *line, char **env)
{
	char		*the_dup;
	int			size_total;
	int			i;
	int			n;
	int			flag;
	int			expand_conter;
	t_expand	*temp;
	t_expand	*head;
	t_inside	inside;

	i = 0;
	inside.quotes = 0;
	inside.dquotes = 0;
	n = 0;
	flag = 0;
	temp = NULL;
	size_total = size_of_expansions(line, &temp, env);
	the_dup = malloc(size_total + 1);
	head = temp;
	while (line[i])
	{
		ft_inside_quotes(&inside, line[i]);
		flag = 0;
		if (temp &&line[i] =='$' && valid_dollar(line, i) && (!inside.quotes))
		{
			i++;
			expand_conter = 0;
			while(temp && temp->expand && temp->expand[expand_conter])
				the_dup[n++] = temp->expand[expand_conter++];
			temp = temp->next;
			while (line[i] && line[i] != ' ' && line[i] != '\"'
					&& line[i] != '\'' && line[i] != '$' && line[i] != '=')
						i++;
			if (line[i] == '$')
				flag = 1;
			if (line[i] == '\'' || line[i] == '"')
				flag = 2;
		}
		if (flag)
		{
			ft_inside_quotes(&inside, line[i]);
			if (line[i] =='$' && valid_dollar(line, i) && (!inside.quotes))
				continue ;
		}
		the_dup[n] = line[i];
		if (!line[i])
			break ;
		n++;
		i++;
	}
	the_dup[n] = '\0';
	temp = head;
	while (temp)
	{
		head = temp->next;
		free(temp);
		temp = NULL;
		temp = head;
	}
	free(line);
	return (the_dup);
}
// echo $PWD'"'$HOME | pwd