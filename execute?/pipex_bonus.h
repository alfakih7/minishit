/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:42:51 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/03 07:34:44 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include "../libft/SRC/libft.h"

typedef struct s_fds
{
	int	fd_input;
	int	fd_output;
	int	ac;
	int	pip[2];
	int	here[2];
}	t_fds;

char	**get_path(char **env);
void	ft_free(void *one_p, char **two_p);
void	execute(char **av, char **env, int i, t_fds	fd);
char	*get_next_line(int fd);
size_t	get_ft_strlen(char *str);
char	*get_ft_strjoin(char *s1, char *s2);
char	*get_ft_strdup(char *s1);
char	*get_ft_strchr(const char *s, int c);
void	without_path(char *av, char **env);
void	with_path(char *av, char **path, char **env);
void	execute_parent(int *pip, char **av, char **env);
void	execute_child(t_fds pip, char **av, char **env);
void	execute_helper(char **av, t_fds *fd, int i);
void	heredoc_decide(char **av, t_fds	*fd, char **env);
void	pipe_decide(char **av, t_fds *fd, char **env, int ac);

#endif