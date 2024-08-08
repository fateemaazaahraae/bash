/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:49:00 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/08 12:46:37 by fbazaz           ###   ########.fr       */
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
        tmp->files = NULL;
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
    int     i; 

    list = NULL;    
    str = ft_split(global_data->cmd, '|');
    i = 0;
    while (str[i])
    {
        new = ft_lstnew(str[i]);
        if (!new)
            printf("Failed to create the node\n");
        ft_lstadd_back(&list, new);
        // free(str[i]);
        i++;
    }
    free(str);
    fill_mini_tokens(list);
    // printf("$$$$$$$$$$$$$$$$$\n");
    remove_quotes(list);
    fill_cmd_args(list);
    return_special_char(list);
    return (list);
}

void    return_from_files(t_redir *files)
{
    t_redir *f;
    int     i;

    f = files;
    while (f)
    {
        i = -1;
        while (f->filename[++i])
        {
            if (is_special(f->filename[i] * (-1), 0))
                f->filename[i] *= -1;
        }
        f = f->next;
    }
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
        while (tmp->cmd_args[++i])
        {
            j = -1;
            while(tmp->cmd_args[i][++j])
            {
                if (is_special(tmp->cmd_args[i][j] * (-1), 3))
                    tmp->cmd_args[i][j] *= -1;
            }
        }
        tmp = tmp->next;   
    }
    return_from_files(list->files);
}
