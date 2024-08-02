/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:59:42 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/08/02 06:30:03 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void exec_heredoc_helper(t_cmd *full_cmd, t_files *files, int *pip)
{
    char *line;

    // Close unused pipe ends in the child process
    close(pip[0]);
    close(pip[1]);
    close(files->heredoc_fd[0]);

    // Read lines from user input until the delimiter is found
    while ((line = readline("> ")) != NULL)
    {
        if (ft_strncmp(line, files->file_name, ft_strlen(files->file_name)) == 0 && line[ft_strlen(files->file_name)] == '\0')
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, files->heredoc_fd[1]);
        ft_putstr_fd("\n", files->heredoc_fd[1]);
        free(line);
    }

    // Close the write end of the heredoc pipe and exit
    close(files->heredoc_fd[1]);
    free_cmd(full_cmd);
    exit(EXIT_SUCCESS);
}

void execute_heredoc(t_cmd *full_cmd, t_files *files, int *pip)
{
    pid_t pid;

    // Create a pipe for heredoc
    if (pipe(files->heredoc_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) // Child process
    {
        exec_heredoc_helper(full_cmd, files, pip);
    }
    else // Parent process
    {
        // Wait for the child process to complete
        if (waitpid(pid, NULL, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        // Close the unused end of the heredoc pipe
        close(files->heredoc_fd[1]);

        // Set up input redirection if needed
        if (files->last_input)
        {
            if (dup2(files->heredoc_fd[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
        close(files->heredoc_fd[0]);
    }
}
