/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:55:06 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/04 15:48:25 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void dup_out_pipe(t_list *list)
{
    if (list->next)
    {
        if (list->outfile > 1)
        {
            dup2(list->outfile, STDOUT_FILENO);
            close(list->outfile);
        }
        else
        {
            dup2(list->pipe_fd[1], STDOUT_FILENO);
            close_pipe(list, 0);
        }
    }
    else if (list->outfile > 1)
    {
        dup2(list->outfile, STDOUT_FILENO);
        close(list->outfile);
    }
    if (is_builtins(list->cmd_args[0]))
    {
        execute_builtins(list);
        exit(0);
    }
}

void restore_stdio(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
}

void save_stdio(int *saved_stdin, int *saved_stdout)
{
    *saved_stdin = dup(STDIN_FILENO);
    *saved_stdout = dup(STDOUT_FILENO);
    if (*saved_stdin == -1 || *saved_stdout == -1)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }
}
