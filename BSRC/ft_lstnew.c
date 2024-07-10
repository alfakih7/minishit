/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:54:31 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/10 04:46:19 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*ft_lstnew(void *content, int type)
{
	t_files	*node;

	node = (t_files *)malloc(sizeof(t_files));
	if (!node)
		return (NULL);
	node->file_name = content;
	node->type = type;
	node->next = NULL;
	return (node);
}
