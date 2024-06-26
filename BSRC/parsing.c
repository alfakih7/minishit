/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/26 09:03:14 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int ac, char **av, char **env)
// {
//     t_tokens *cmd;
//     char *str;
//     int   i;

//     while(42)
//     {
//         printf("minishell > \n");
//         str = get_next_line(0);
//         check_quotes(str);
//         cmd = split_with_no_quotes(str, '|');
//         i = 0;
//         check_quotes(str);
//         while (cmd)
//         {
//             printf("cmd[%d] = %s\n",i , cmd->content);
//             cmd = cmd->next;
//             i++;
//         }
//         printf("num of pipes = %d\n", split_with_no_quotes_len(str, '|'));
//         if (ft_strchr(str, '\"'))
//             return (1);
//     }
//     return (0);
// }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// A function prototype for ft_split and get_next_line.
// Assuming these functions are defined somewhere in your codebase.

int main(int ac, char **av, char **env)
{
    char *str;
    char *bash_cmd[4];
    int i;

    bash_cmd[0] = "/bin/bash";
    bash_cmd[1] = "-c";
    bash_cmd[3] = NULL;

    while (1)
    {
        write(1, "minishell > ", 11);
        str = get_next_line(0);

        if (str == NULL)
        {
            break; // Exit loop if no input
        }

        // Remove the newline character from str, if it exists
        str[strcspn(str, "\n")] = 0;

        // Skip empty input
        if (strlen(str) == 0)
        {
            free(str);
            continue;
        }

        // Prepare the command for bash
        bash_cmd[2] = str;

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == 0)
        {
            // Child process: execute the command
            if (execve("/bin/bash", bash_cmd, env) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            // Fork failed
            perror("fork");
        }
        else
        {
            // Parent process: wait for the child to finish
            int status;
            waitpid(pid, &status, 0);
        }

        free(str); // Free the allocated memory for the input string
    }

    return 0;
}

// Dummy implementation of get_next_line
