/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstaddback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:00:12 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/21 17:30:17 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static t_cmd	*ft_cmdlstlast(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_cmdlstadd_back(t_cmd **lst, t_cmd *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ft_cmdlstlast(*lst)->next = new;
}
