/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:37:00 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/13 07:40:19 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_expand	*expand_lstlast(t_expand *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_expand	*expand_lstnew(void *content)
{
	t_expand	*node;

	node = (t_expand *)malloc(sizeof(t_expand));
	if (!node)
		return (NULL);
	node->expand = content;
	node->next = NULL;
	return (node);
}

void	expand_lstadd_back(t_expand **lst, t_expand *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		expand_lstlast(*lst)->next = new;
}