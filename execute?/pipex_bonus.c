/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:42:30 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/03 06:44:22 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_fds	fd;

	if (!(ft_strncmp(av[1], "here_doc", 9)))
	{
		if (ac == 6)
			heredoc_decide(av, &fd, env);
		else
		{
			write(2, "wrong number of args\n", 22);
			return (1);
		}
	}
	else if (ac >= 5)
		pipe_decide(av, &fd, env, ac);
	else
	{
		write(2, "wrong number of args\n", 22);
		return (1);
	}
}
