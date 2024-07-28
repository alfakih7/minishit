/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_ult_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 03:02:03 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/28 23:28:59 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	if (files->fd == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror("bash: ");
		exit (1);
	}
	// printf("files->last_output = %d\n", files->last_output);
	if (files->last_output)
		dup2(files->fd, 1);
	close(files->fd);
	return (0);
}

static int	dup_in(t_files *files, int *fd)
{
	if (files->type == REDIR_IN)
	{
		files->fd = open(files->file_name, O_RDONLY);
		if (files->fd == -1)
		{
			close(fd[0]);
			close(fd[1]);
			perror("bash: ");
			exit (1);
		}
		if (files->last_input)
			dup2(files->fd, 0);
		close(files->fd);
	}
	else if (files->type == REDIR_HEREDOC)
		execute_heredoc(files, fd); 
	return (0);
}
void	the_ultimate_dup(t_files *files, int *fd)
{
	last_in_and_out(files);
	while(files)
	{
		if (files->type == REDIR_OUT || files->type == REDIR_APPEND)
			dup_out(files, fd);
		else if (files->type == REDIR_IN || files->type == REDIR_HEREDOC)
			dup_in(files, fd);
		files = files->next;
	}
}
