/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:29:45 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/08/02 06:30:20 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static void	my_waitpid(pid_t *pid, int size, int *status)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], status, 0);
		i++;
	}
}
void	pipe_decide(t_cmd *cmd, char **env, int tmp_fd[2])
{
	pid_t	*pid;
	t_cmd	*temp;
	int		status;
	int		i;
	int		size;
	int		fd[2];

	i = 0;
	temp = cmd;
	size = ft_cmdlstsize(cmd);
	if (size)
		pid = malloc(sizeof(pid_t) * size);
	while (i < size && temp)
	{
		pipe(fd);
		// waitpid(pid, &status, 0);
		pid[i] = fork();
		if (!pid[i])
		{
			close(tmp_fd[0]);
			close(tmp_fd[1]);
			ft_free(pid, NULL);
			execute(cmd, temp, env, fd);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			if (i == size - 1)
			{
				my_waitpid(pid, size, &status);
				ft_free(pid, NULL);
				(WEXITSTATUS(status)); /// the exit status
			}
			temp = temp->next;
			i++;
		}
	}
}
