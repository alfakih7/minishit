/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_ult_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 03:02:03 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/08/02 06:30:13 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	last_in_and_out(t_files *files)
{
	t_files	*tmp;
	t_files	*head;

	tmp = NULL;
	head = files;
	while (files)
	{
		if (files->type == REDIR_IN || files->type == REDIR_HEREDOC)
			tmp = files;
		files = files->next;
	}
	if (tmp)
		tmp->last_input = 1;
	files = head;
	tmp = NULL;
	while(files)
	{
		if (files->type == REDIR_OUT || files->type == REDIR_APPEND)
			tmp = files;
		files = files->next;
	}
	if (tmp)
		tmp->last_output = 1;
}
static int	dup_out(t_files *files, int *fd)
{
	if (files->type == REDIR_OUT)
		files->fd = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (files->type == REDIR_APPEND)
		files->fd = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// if (files->fd == -1)
	// {
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	perror("bash: ");
	// 	return (1);
	// }
	// if (files->last_output)
	// 	dup2(files->fd, 1);
	// close(files->fd);
	return (0);
}

static int	dup_in(t_cmd *full_cmd, t_files *files, int *fd)
{
	if (files->type == REDIR_IN)
	{
		files->fd = open(files->file_name, O_RDONLY);
		if (files->fd == -1)
		{
			close(fd[0]);
			close(fd[1]);
			perror("bash: ");
			return (1);
		}
		if (files->last_input)
			dup2(files->fd, 0);
		close(files->fd);
	}
	else if (files->type == REDIR_HEREDOC)
		execute_heredoc(full_cmd, files, fd); 
	return (0);
}
int	the_ultimate_dup(t_cmd *full_cmd, t_files *files, int *fd)
{
	int	status;

	status = 0;
	last_in_and_out(files);
	while(files)
	{
		if (files->type == REDIR_OUT || files->type == REDIR_APPEND)
			status = dup_out(files, fd);
		else if (files->type == REDIR_IN || files->type == REDIR_HEREDOC)
			status = dup_in(full_cmd, files, fd);
		if (status)
			return (status);
		files = files->next;
	}
	return (status);
}
