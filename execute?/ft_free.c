/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:57:29 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/01 04:17:32 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// flag 0 is for strings and arrays
// flag 1 is for file_descriotors

void	ft_free(void *one_p, char **two_p)
{
	int	i;

	i = -1;
	if (one_p)
	{
		free(one_p);
		one_p = NULL;
	}
	if (two_p)
	{
		while (two_p[++i])
			free(two_p[i]);
		free(two_p);
		two_p = NULL;
	}
}
