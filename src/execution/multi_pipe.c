/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:18:25 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/30 19:28:21 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int    execute_cmd(t_list *list)
{
    // if (list->next)
        if (pipe(list->pipe_fd) == -1)
            return (exit_func(PIPE_ERR, NULL), 1);
    if (list->infile > 0)
    {
        dup2(list->infile, STDIN_FILENO);
        close(list->infile);
    }
    list->pid = fork_process();
    if (!list->pid)
    {
        if (list->infile == -1 || list->outfile == -1)
            exit(1);
        dup_out_pipe(list);
            ft_execve(list);
    }
    else
    {
        dup2(list->pipe_fd[0], STDIN_FILENO);
        close_pipe(list);
    }
    return (0);
}
