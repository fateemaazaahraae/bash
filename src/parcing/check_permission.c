/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:00:31 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/31 12:13:33 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int check_in(t_list *tmp)
{
    while (tmp->in)
    {
        if (access(tmp->in->name, F_OK) == -1)
        {
            printf("minishell: %s: No such file or directory\n", tmp->in->name);
            tmp->infile = -1;
            return (-1);
        }
        if (access(tmp->in->name, R_OK) == -1)
        {
            printf("minishell: %s: Permission denied\n", tmp->in->name);
            tmp->infile = -1;
            return (-1);
        }
        if (!tmp->in->next)
            tmp->infile = tmp->in->fd;
        tmp->in = tmp->in->next;
    }
    return (0);
}

int check_out(t_list *tmp)
{
    while (tmp->out)
    {
        if (access(tmp->out->name, F_OK) == -1)
        {
            printf("minishell: %s: No such file or directory\n", tmp->out->name);
            tmp->outfile = -1;
            return (-1);
        }
        if (access(tmp->out->name, W_OK) == -1)
        {
            printf("minishell: %s: Permission denied\n", tmp->out->name);
            tmp->outfile = -1;
            return (-1);
        }
        if (!tmp->out->next)
            tmp->outfile = tmp->out->fd;
        tmp->out = tmp->out->next;
    }
    return (0);
}

void check_files(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp)
    {
        if (check_in(tmp))
        {
            tmp = tmp->next;
            continue;
        }
        if (check_out(tmp))
        {
            tmp = tmp->next;
            continue;
        }
        tmp = tmp->next;
    }
}
