/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:54:23 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/30 15:12:00 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void ft_lstclear2(t_list **lst)
{
    t_list *temp;

    if (!lst)
        return;

    while (*lst)
    {
        temp = (*lst)->next;
        free((*lst)->content);
        free(*lst);
        *lst = temp;
    }
    *lst = NULL;
}

void free_2D(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str[i]);
}

void    ft_free_struct(t_list **list)
{
    while (*list)
    {
        free_2D((*list)->mini_tokens);
        free_2D((*list)->cmd_args);
        free((*list)->limiter);
        ft_lstclear_redir(&((*list)->in));
        ft_lstclear_redir(&((*list)->out));
        *list = (*list)->next;
    }
    ft_lstclear2(&((*list)));
}