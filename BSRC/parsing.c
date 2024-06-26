/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/26 11:25:56 by almohame         ###   ########.fr       */
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
int main(int ac, char **av, char **env)
{
    t_tokens *cmd;
    int   i;
    char *line_chunk;
    int ptr = 0;
    t_file *redirect;

    while(42)
    {
        printf("minishell > \n");
        line_chunk = get_next_line(0);
        // cmd = split_with_no_quotes(str, '|');
        i = 0;
        check_quotes(line_chunk);
        while (line_chunk[ptr]) {
        redirect = ms_get_next_redirect(line_chunk, '>', &ptr);
        if (redirect) {
            printf("Redirect: %s, Extra: %d\n", redirect->name, redirect->is_extra);
            free(redirect->name);
            free(redirect);
        }
        // while (cmd)
        // {
        //     printf("cmd[%d] = %s\n",i , cmd->content);
        //     cmd = cmd->next;
        //     i++;
        // }
        // printf("num of pipes = %d\n", split_with_no_quotes_len(str, '|'));
        // if (ft_strchr(str, '\"'))
        //     return (1);
    }
    return (0);
}
}