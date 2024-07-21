/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:04 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/20 16:34:54 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *the_env)
{
	if (the_env)
	{
		while (*the_env)
		{
			if (*the_env == '=')
				return (++the_env);
			the_env++;
		}
		return the_env;
	}
	return (NULL);
}
