/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:00:31 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 12:23:58 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int check_in(t_redir *infile)
{
    t_redir *in;

    in = infile;
    while (in)
    {
        if (in->name[0] == '$')
            return (exit_func(AMBIGUOUS, in->name), -1); 
        if (ft_strcmp(in->name, "/dev/stdin"))
        {
            if (in->type == INPUT)
                in->fd = open(in->name, O_RDONLY);
            if (access(in->name, F_OK) == -1)
                return (exit_func(NO_SUCH_FILE, in->name), -1);
            if (access(in->name, R_OK) == -1)
                return (exit_func(PERR_DENIED, in->name), -1);
        }
        else
            in->fd = 0;
        in = in->next;
    }
    return (0);
}

int check_out(t_redir *outfile)
{
    t_redir *out;

    out = outfile;
    while (out)
    {
        if (out->name[0] == '$')
            return (exit_func(AMBIGUOUS, out->name), -1);      
        if (ft_strcmp(out->name, "/dev/stdout"))
        {
            if (out->type == OUTPUT)
                out->fd = open(out->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (out->type == APPEND)
                out->fd = open(out->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (access(out->name, F_OK) == -1)
                return (exit_func(NO_SUCH_FILE, out->name), -1);
            if (access(out->name, W_OK) == -1)
                return (exit_func(PERR_DENIED, out->name), -1);
        }
        else
            out->fd = 1;
        out = out->next;
    }
    return (0);
}

int open_files(t_list *list)
{
    if (check_in(list->in))
        return (-1);
    if (check_out(list->out))
        return (-1);
    return (0);
}
