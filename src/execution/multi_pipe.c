/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:18:25 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/05 16:32:40 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int    execute_cmd(t_list *list)
{
    if (list->limiter)
        here_doc(list);
    open_pipes(list->pipe_fd);
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
        // wait(NULL);
        dup2(list->pipe_fd[0], STDIN_FILENO);
        close_pipe(list, 0);
    }
    return (0);
}
