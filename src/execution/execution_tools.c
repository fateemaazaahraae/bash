/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:12:30 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/07 20:12:16 by fbazaz           ###   ########.fr       */
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

// void    wait_child(t_list *list)
// {
//     int status;

//     waitpid(list->pid, &status, 0);
//     global_data->exit_status = WEXITSTATUS(status);
//     if (status == 2)
//     {
//         global_data->exit_status = VAL_SIGINT;
//         ft_putendl_fd("^C", STDERR_FILENO);
//     }
//     else if (status == 3)
//     {
//         global_data->exit_status = VAL_SIGQUIT;
//         ft_putendl_fd("Quit: 3", STDERR_FILENO);
//     }
//     else if (WIFSIGNALED(status))
//         global_data->exit_status = WTERMSIG(status) + 128;
//     while (wait(NULL) != -1)
//         ;
// }

void wait_child(t_list *list)
{
    int status;

    waitpid(list->pid, &status, 0);
    if (WIFEXITED(status))
        global_data->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        if (sig == SIGINT)
        {
            global_data->exit_status = VAL_SIGINT;
            ft_putendl_fd("^C", STDERR_FILENO);
        }
        else if (sig == SIGQUIT)
        {
            global_data->exit_status = VAL_SIGQUIT;
            ft_putendl_fd("Quit: 3", STDERR_FILENO);
        }
        else
            global_data->exit_status = sig + 128;
    }
    while (wait(NULL) != -1)
        ;
}

