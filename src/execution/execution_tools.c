/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:12:30 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 16:49:46 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    open_pipes(int *pipe_fd)
{
    if (pipe(pipe_fd) == -1)
    {
        exit_func(PIPE_ERR, NULL);
        exit(EXIT_FAILURE);
    }
}

pid_t    fork_process()
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        exit_func(FORK_ERR, NULL);
        exit(EXIT_FAILURE);
    }
    return (pid);
}

void    close_pipe(t_list *list, int i)
{
    if (i == 0)
    {
        if (list->pipe_fd[0] != 0)
            close(list->pipe_fd[0]);
        if (list->pipe_fd[1] != 1)
            close(list->pipe_fd[1]);
    }
    else
    {
        if (list->heredoc_fd[0] != 0)
            close(list->heredoc_fd[0]);
        if (list->heredoc_fd[1] != 1)
            close(list->heredoc_fd[1]);
    }
}
