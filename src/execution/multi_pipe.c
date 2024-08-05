/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:18:25 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/05 19:06:31 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    dup_infile(t_redir *infile)
{
    t_redir *in;

    in = infile;
    while (in)
    {
        if (in->fd == STDIN_FILENO && !ft_strcmp(in->name, "/dev/stdin")) // it means that name = /dev/stdin
        {
            in = in->next;
            continue;
        }
        dup2(in->fd, STDIN_FILENO);
        close(in->fd);
        in = in->next;
    }
}

int    execute_cmd(t_list *list)
{
    open_pipes(list->pipe_fd);
    list->pid = fork_process();
    if (!list->pid)
    {
        if (open_files(list))
            exit(1);
        if (list->in)
            dup_infile(list->in);
        dup_out_pipe(list);
        ft_execve(list);
    }
    else
    {
        dup2(list->pipe_fd[0], STDIN_FILENO);
        close_pipe(list, 0);
    }
    return (0);
}
