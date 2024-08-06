/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:00:31 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 19:40:17 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int check_in(t_list *list)
{
    t_redir *in;

    in = list->in;
    while (in)
    {
        if (in->filename[0] == '$' && in->type != HERE_DOC)
            return (exit_func(AMBIGUOUS, in->filename), -1); 
        if (ft_strcmp(in->filename, "/dev/stdin"))
        {
            in->fd = open(in->filename, O_RDONLY);
            if (in->type == INPUT)
            {
                if (access(in->filename, F_OK) == -1)
                    return (exit_func(NO_SUCH_FILE, in->filename), -1);
                if (access(in->filename, R_OK) == -1)
                    return (exit_func(PERR_DENIED, in->filename), -1);
            }
            dup2(in->fd, STDIN_FILENO);
            if (in->fd != 0)
                close(in->fd);
        }
        else
            in->fd = 0;
        in = in->next;
    }
    return (0);
}

int check_out(t_list *list)
{
    t_redir *out;

    out = list->out;
    while (out)
    {
        if (out->filename[0] == '$')
            return (exit_func(AMBIGUOUS, out->filename), -1);      
        if (ft_strcmp(out->filename, "/dev/stdout"))
        {
            if (out->type == OUTPUT)
                out->fd = open(out->filename,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (out->type == APPEND)
                out->fd = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (access(out->filename, F_OK) == -1)
                return (exit_func(NO_SUCH_FILE, out->filename), -1);
            if (access(out->filename, W_OK) == -1)
                return (exit_func(PERR_DENIED, out->filename), -1);
        }
        else
            out->fd = 1;
        out = out->next;
    }
    return (0);
}

int open_files(t_list *list)
{
    if (check_in(list))
        return (-1);
    if (check_out(list))
        return (-1);
    return (0);
}
