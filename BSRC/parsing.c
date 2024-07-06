/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 13:25:30 by almohame         ###   ########.fr       */
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


int main(int argc, char **argv, char **envp) {
    char *line_chunk;
    t_cmd_chunk **commands;
    char **pipelines;
    int i = 0;

    while (1) {
        printf("minishell > \n");
        line_chunk = get_next_line(0); // Read input line

        if (line_chunk == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        printf("Input line: %s\n", line_chunk); // Debug: Print input line

        pipelines = split_with_no_quotes(line_chunk, '|'); // Split by '|'
        size_t num_pipelines = split_with_no_quotes_len(line_chunk, '|'); // Count pipelines
        i = 0;
        while (pipelines[i])
            printf("splii %d: %s\n", i, pipelines[i++]);
        i = 0;
        commands = ms_command_chunks_get(pipelines, num_pipelines); // Parse commands
        
        

        i = 0;
        while (commands[i] != NULL) {
            printf("Inputs for Command %d:\n", i + 1);
            t_list *input = commands[i]->inputs;
            int input_index = 1;
            while (input != NULL) {
                printf("Input %d: %s\n", input_index, (char *)input->content); // Print inputs
                input = input->next;
                input_index++;
            }
            i++;
        }

        // Clean up allocated memory
        free(line_chunk);
        ft_split_destroy(pipelines);

        // Clean up commands array
        i = 0;
        while (commands[i] != NULL) {
            ft_lstclear(&(commands[i]->inputs), free);
            ft_lstclear(&(commands[i]->outputs), free);
            free(commands[i]->cmd); // Assuming cmd is dynamically allocated
            free(commands[i]);
            i++;
        }
        free(commands);
    }

    return 0;
}
