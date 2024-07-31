/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:29:37 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/29 16:38:39 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

static  void expand_file_name(t_files *files, char  **env)
{
	while (files)
	{
		files->file_name = expansion(files->file_name, env);
		files = files->next;
	}
}

static char *get_file_name(char *splitted)
{
	int	i;

	i = 0;
	while (splitted[i] == '<' || splitted[i] == '>')
		i++;
	return (ft_strdup(&splitted[i]));
}

static char	*file_name(char *splitted)
{
	int	i;
	i = 0;
	while (splitted[i] == '<' || splitted[i] == '>')
		i++;
	if (!splitted[i])
		return (NULL);
	else
		return (get_file_name(splitted));
}

static char	**fill_cmd(char **command, char *cont)
{
	int		i;
	int		size;
	char	**new_cmd;

	i = 0;
	size = 0;
	if (command)
	{
		while (command[size])
			size++;
	}
	new_cmd = malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (NULL);
	if (command)
	{
		while (command[i])
		{
			new_cmd[i] = ft_strdup(command[i]);
			i++;
		}
		ft_free(NULL, command);
	}
	new_cmd[i++] = cont;
	new_cmd[i] = NULL;
	return (new_cmd);
}

t_cmd	*ft_redirection(char **env, char *line, int num)
{
	t_cmd	*command;
	t_files	*the_list;
	int		type;
	char	*cmd;
	char	**splitted;
	int		i;
	int		n;
	int		l;
	char	*file;

	command = malloc(sizeof(t_cmd));
	command->content = NULL;
	the_list = NULL;
	i = -1;
	splitted = split_with_no_quotes(line, ' ');  /////// 2 errors on split_with_no_quotes      1 = unclosed ' inside a ""  2 = the delemiters at the last are not trimmed 
	// splitted = ft_split(line, ' ');
	while (splitted && splitted[++i])
	{
		if (splitted[i][0] == '<' || splitted[i][0] == '>')
		{
			if (splitted[i][1] && splitted[i][1] == '<')
				type = REDIR_HEREDOC;
			else if (splitted[i][1] && splitted[i][1] == '>')
				type = REDIR_APPEND;
			else if (splitted[i][0] == '<')
				type = REDIR_IN;
			else if (splitted[i][0] == '>')
				type = REDIR_OUT;
			file = (file_name(splitted[i]));
			if (!file)
				ft_lstadd_back(&the_list, ft_lstnew(ft_strdup(splitted[++i]), type));
			else
				ft_lstadd_back(&the_list, ft_lstnew(file, type));
		}
		else
		{
			if (splitted[i])
			{
				cmd = expansion(ft_strdup(splitted[i]), env);
				command->content = fill_cmd(command->content, (cmd));
			}
		}
	}
	ft_free(NULL, splitted);
	expand_file_name(the_list, env);
	command->cmd_num = num;
	command->redirect = the_list;
	command->next = NULL;
	return (command);
}
