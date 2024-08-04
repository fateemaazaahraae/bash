/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:49:00 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/04 16:38:15 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void fill_mini_tokens(t_list *list)
{
    t_list *tmp;

    tmp = list;  
    while (tmp)
    {
        tmp->mini_tokens = ft_split(tmp->content, ' ');
        tmp->out = NULL;
        tmp->in = NULL;
        tmp->limiter = NULL;
        tmp = tmp->next;
    }
}

t_list    *ft_fill_tokens()
{
    char **str;
    t_list *list;
    t_list  *new;

    list = NULL;
    str = ft_split(global_data->cmd, '|');
    int i = -1;
    while (str[++i])
    {
        new = ft_lstnew(str[i]);
        if (!new)
            printf("Failed to create the node\n");
        ft_lstadd_back(&list, new);
        free(str[i]);
    }
    free(str);
    fill_mini_tokens(list);
    return_special_char(list);
    fill_cmd_args(list);
    check_files(list);
    return (list);
}
