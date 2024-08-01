/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:07:54 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/24 17:27:46 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void ft_lstclear_limiter(t_limiter **lst)
{
    t_limiter *tmp;

    if (!lst)
        return;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->lim);
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}

t_limiter	*ft_lstnew_limiter(char *name)
{
	t_limiter	*node;

	node = malloc(sizeof(t_limiter));
	node->lim = ft_strdup(name);
	node->next = NULL;
	return (node);
}

t_limiter	*ft_lstlast_limiter(t_limiter *limiter)
{
	if (!limiter)
		return (NULL);
	while (limiter->next != NULL)
		limiter = limiter->next;
	return (limiter);
}

void ft_lstadd_back_limiter(t_limiter **limiter, t_limiter *new)
{
    t_limiter *tmp;

    if (!new)
        return ;
    if (!limiter || !(*limiter))
    {
        *limiter = new;
        return ;
    }
    tmp = ft_lstlast_limiter(*limiter);
    tmp->next = new;
}
