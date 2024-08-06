/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:49:00 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/06 20:26:42 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*this function split each list content by space and store it in mini_tokens*/
void fill_mini_tokens(t_list *list)
{
    t_list *tmp;

    tmp = list;  
    while (tmp)
    {
        tmp->mini_tokens = ft_split(tmp->content, ' ');
        tmp->out = NULL;
        tmp->in = NULL;
        tmp = tmp->next;
    }
}

/*this function create our linked list so first it split our cmd by | then it create linked list
    between 2 nodes there is a pipe then it fill mini_tokens (split by space) and return special
    to there initial state and fill cmd_args and open files*/
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
    return (list);
}

/* this function return the special char to there initial value cuz we multiple it by -1*/
void    return_special_char(t_list *list)
{
    int i;
    int j;

    t_list *tmp;
    tmp = list;
    while (tmp)
    {
        i = -1;
        while (tmp->mini_tokens[++i])
        {
            j = -1;
            while(tmp->mini_tokens[i][++j])
            {
                if (is_special(tmp->mini_tokens[i][j] * (-1), 3))
                    tmp->mini_tokens[i][j] *= -1;
            }
        }
        tmp = tmp->next;   
    }
}
