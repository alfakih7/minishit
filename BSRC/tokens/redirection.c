/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:29:37 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 20:19:27 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char *file;

	i = 0;
	printf("str =  %s\n", splitted);
	while (splitted[i] == '<' || splitted[i] == '>')
		i++;
	if (!splitted[i])
		return (NULL);
	else
		return (get_file_name(splitted));
}

t_files	*ft_redirection(char *line)
{
	t_files	*the_list;
	int type;
	char	**splitted; //// splitted by spaces
	int		i;
	char	*file;

	the_list = NULL;
	i = 0;
	splitted = split_with_no_quotes(line, ' ');
	while (splitted && splitted[i])
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
			file = file_name(splitted[i]);
			if (!file)
			{
				++i;
				ft_lstadd_back(&the_list, ft_lstnew(splitted[i], type));
			}
			else
				ft_lstadd_back(&the_list, ft_lstnew(file, type));
		}
		i++;
	}
	return (the_list);
}
