/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:54:31 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/26 05:13:17 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_lstnew(void *content)
{
	t_tokens	*node;

	node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
