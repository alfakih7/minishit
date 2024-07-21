/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/20 22:58:35 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>

// Define ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const char *redirection_type_to_string(enum RedirectionType type)
{
    switch (type)
    {
        case REDIR_IN: return "REDIR_IN";
        case REDIR_HEREDOC: return "REDIR_HEREDOC";
        case REDIR_OUT: return "REDIR_OUT";
        case REDIR_APPEND: return "REDIR_APPEND";
        default: return "UNKNOWN";
    }
}

static void printlist(t_files *file)
{
    while (file)
    {
        printf("  %s  type = %s%s%s  file_name = %s%s%s\n",
               ANSI_COLOR_CYAN, ANSI_COLOR_YELLOW, redirection_type_to_string(file->type), ANSI_COLOR_CYAN,
               ANSI_COLOR_BLUE, file->file_name, ANSI_COLOR_RESET);
        file = file->next;
    }
}
void	ft_free(void *one_p, char **two_p)
{
	int	i;

	i = -1;
	if (one_p)
	{
		free(one_p);
		one_p = NULL;
	}
	if (two_p)
	{
		while (two_p[++i])
			free(two_p[i]);
		free(two_p);
		two_p = NULL;
	}
}
void	free_cmd(t_cmd *cmd)
{
	t_files *temp;
	
	if (!cmd)
		return ;
	ft_free(NULL, cmd->content);
	while (cmd->redirect)
	{
		ft_free(cmd->redirect->file_name, NULL);
		temp = cmd->redirect->next;
		free(cmd->redirect);
		cmd->redirect = NULL;
		cmd->redirect = temp;
	}
	free(cmd);
}

int main(int argc, char **argv, char **envp)
{
    int         i;
    int         n;
    t_cmd       *redirections;
    char        *line_chunk;
    char        **cmd; //splitted by pipes
	char *temp;

    i = -1;
	redirections = NULL;
	line_chunk = NULL;
    while (1)
    {
        line_chunk = readline("\x1b[34mminishell > \x1b[0m");
        if (!line_chunk)
        {
			clear_history();
            printf(ANSI_COLOR_RED "Error: Failed to read input.\n" ANSI_COLOR_RESET);
			if (redirections)
				free_cmd(redirections);
            break;
        }
		add_history(line_chunk);
        if (!check_quotes(line_chunk) && check_syntax(line_chunk))
        {
            cmd = split_with_no_quotes(line_chunk, '|');
    		n = -1;
            while (cmd[++n])
            {
                printf(ANSI_COLOR_MAGENTA "------------cmd[%d]------------\n" ANSI_COLOR_MAGENTA, n);
				temp = joined_str(cmd[n]);
                redirections = ft_redirection(envp, temp);
                printf(ANSI_COLOR_YELLOW "----- Redirections -----\n" ANSI_COLOR_RESET);
                printlist(redirections->redirect);
                printf(ANSI_COLOR_CYAN "------------------------\n" ANSI_COLOR_RESET);
                i = -1;
                printf(ANSI_COLOR_GREEN "-------- Commands -------\n" ANSI_COLOR_RESET);
                while ((redirections->content && redirections->content[++i]))
                    printf(ANSI_COLOR_GREEN "cmd [%d] = (%s%s%s)\n", i, ANSI_COLOR_MAGENTA, redirections->content[i], ANSI_COLOR_RESET);
                printf(ANSI_COLOR_CYAN "------------------------\n" ANSI_COLOR_RESET);
				free (temp);
				if (redirections)
					free_cmd(redirections);
				redirections = NULL;
            }
			ft_free(NULL,cmd);
        }
		else
		{
			// printf("true = %d\n", check_quotes(line_chunk));
			// printf("true = %d\n", check_syntax(line_chunk));
			ft_putstr_fd(ANSI_COLOR_RED "syntax error\n" ANSI_COLOR_RESET, 2);
			free(line_chunk);
			line_chunk = NULL;
		}
		if (redirections)
			free_cmd(redirections);
		redirections = NULL;
    }
    return 0;
}