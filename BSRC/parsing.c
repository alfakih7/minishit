/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/13 15:49:42 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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


int main(int argc, char **argv, char **envp)
{
    int         i;
    t_cmd       *redirections;
    char        *line_chunk;
    char        **cmd; //splitted by pipes

    i = -1;
    while (1)
    {
        printf(ANSI_COLOR_CYAN "minishell > " ANSI_COLOR_RESET);
        fflush(stdout);  // Ensure the prompt is displayed immediately
        line_chunk = get_next_line(0);
        if (!line_chunk)
        {
            printf(ANSI_COLOR_RED "Error: Failed to read input.\n" ANSI_COLOR_RESET);
            break;
        }
        check_quotes(line_chunk);
        if (!check_syntax(line_chunk))
            ft_putstr_fd(ANSI_COLOR_RED "syntax error\n" ANSI_COLOR_RESET, 2);
        else
        {
            cmd = split_with_no_quotes(line_chunk, '|');
            if (cmd)
            {
                redirections = ft_redirection(envp, joined_str(cmd[0]));
                printf(ANSI_COLOR_YELLOW "----- Redirections -----\n" ANSI_COLOR_RESET);
                printlist(redirections->redirect);
                printf(ANSI_COLOR_CYAN "------------------------\n" ANSI_COLOR_RESET);
                i = -1;
                printf(ANSI_COLOR_GREEN "-------- Commands -------\n" ANSI_COLOR_RESET);
                while ((redirections->content && redirections->content[++i]))
                    printf(ANSI_COLOR_GREEN "cmd [%d] = (%s%s%s)\n", i, ANSI_COLOR_MAGENTA, redirections->content[i], ANSI_COLOR_RESET);
                printf(ANSI_COLOR_CYAN "------------------------\n" ANSI_COLOR_RESET);
            }
        }
    }
    return 0;
}