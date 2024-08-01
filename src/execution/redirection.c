/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:55:06 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/30 19:27:26 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    close_pipe(t_list *list)
{
    close(list->pipe_fd[0]);
    close(list->pipe_fd[1]);
}

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
            close_pipe(list);
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

void here_doc(t_list *list)
{
    int heredoc_fd[2];
    char *line;
    
    while (list->limiter)
    {
        if (pipe(heredoc_fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        while ((line = readline("> ")) != NULL)
        {
            if (!ft_strcmp(line, list->limiter->lim))
            {
                free(line);
                break;
            }
            write(heredoc_fd[1], line, ft_strlen(line));
            write(heredoc_fd[1], "\n", 1);
            free(line);
        }
        if (list->limiter->next)
        {
            close(heredoc_fd[0]);
            close(heredoc_fd[1]);
        }
        list->limiter = list->limiter->next;
    }
    close(heredoc_fd[1]);
    dup2(heredoc_fd[0], STDIN_FILENO);
    close(heredoc_fd[0]);
}
