/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:42:30 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/23 17:40:53 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int	the_exectue(t_cmd *cmd ,char **env)
{
	int		size;
	int		tmp_fd[2];
	t_fds	fd;

	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	size = ft_cmdlstsize(cmd);
	// if (size)
	// {
		// printf("size == %d\n", size);
		// return (0);
	// }
	// if (size == 1)
	// 	execute_one(cmd, env);
	// else
	pipe_decide(cmd, env, tmp_fd);
	dup2(tmp_fd[0], STDIN_FILENO);
	dup2(tmp_fd[1], STDOUT_FILENO);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
	// t_fds	fd;

	// if (ac == 2)
	// 	execute_one(av, env);
	// if (!(ft_strncmp(av[1], "here_doc", 9)))
	// {
	// 	if (ac == 6)
	// 		heredoc_decide(av, &fd, env);
	// 	else
	// 	{
	// 		write(2, "wrong number of args\n", 22);
	// 		return (1);
	// 	}
	// }
	// else if (ac >= 5)
	// 	pipe_decide(av, &fd, env, ac);
	// else
	// {
	// 	write(2, "wrong number of args\n", 22);
	// 	return (1);
	// }
	return (0);
}
