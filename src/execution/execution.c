/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:16:28 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/07 13:35:46 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int    execute_cmd(t_list *list)
{
    open_pipes(list->pipe_fd);
    list->pid = fork_process();
    if (!list->pid)
    {
        if (open_files(list))
            exit (1);
        dup_out_pipe(list);
        if (is_builtins(list->cmd_args[0]))
        {
            execute_builtins(list);
            exit(0);
        }
        else
            ft_execve(list);
    }
    else
    {
        dup2(list->pipe_fd[0], STDIN_FILENO);
        close_pipe(list, 0);
    }
    return (0);
}

void    run_execution(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp)
    {
        if (execute_cmd(tmp))
        {
            tmp = tmp->next;
            continue ;
        }
        tmp = tmp->next;
    }
    tmp = list;
    while (tmp)
    {
        if (tmp->pid >= 0)
            waitpid(tmp->pid, &global_data->exit_status, 0);
        tmp = tmp->next;
    }
}

void    execution(t_list *list)
{
    int stdin;
    int stdout;

    save_stdio(&stdin, &stdout);
    if (ft_lstsize(list) == 1 && is_builtins(list->cmd_args[0]))
    {
        if (open_files(list))
        {
            restore_stdio(stdin, stdout);
            return ;
        }
        // dup_outfile(list->files);
        execute_builtins(list);
        restore_stdio(stdin, stdout);
        return ;
    }
    run_execution(list);
    restore_stdio(stdin, stdout);
}
