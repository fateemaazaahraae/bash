/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:16:28 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/04 16:45:35 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    run_execution(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp)
    {
        if (tmp->limiter)
            here_doc(tmp);
        if (execute_cmd(tmp))
            break;
        if (tmp->outfile != 1)
			close(tmp->outfile);
        tmp = tmp->next;
    }
    tmp = list;
    while (tmp)
    {
        if (tmp->pid >= 0)
            waitpid(tmp->pid, &global_data->exit_status, 0);
        tmp = tmp->next;
    }
    // while (wait(NULL) > 0);
}

void    execution(t_list *list)
{
    int stdin;
    int stdout;

    save_stdio(&stdin, &stdout);
    if (ft_lstsize(list) == 1 && is_builtins(list->cmd_args[0]))
    {
        if (list->infile == -1 || list->outfile == -1)
            return ;
        execute_builtins(list);
        restore_stdio(stdin, stdout);
        return ;
    }
    run_execution(list);
    restore_stdio(stdin, stdout);
}


// void    red_one_command(t_list *list)
// {
//     t_redir *in;
//     t_redir *out;

//     in = ft_lstlast_redir(list->in);
//     out = ft_lstlast_redir(list->out);
//     if (in)
//     {
//         dup2(in->fd, STDIN_FILENO);
//         close(in->fd);
//     }
//     if (out)
//     {
//         dup2(out->fd, STDOUT_FILENO);
//         close(out->fd);
//     }
// }

// void    execute_one(t_data *data)
// {
//     int pid;
//     int saved_stdin;
//     int saved_stdout;

//     save_stdio(&saved_stdin, &saved_stdout);
//     if (data->list->limiter)
//         here_doc(data->list);
//     red_one_command(data->list);
//     if (is_builtins(data->list->cmd_args[0]))
//         execute_builtins(data, data->list);
//     else
//     {
//         pid = fork_process();
//         if (pid == 0)
//             handle_child_process(data);
//         else
//             wait(NULL);
//     }
//     restore_stdio(saved_stdin, saved_stdout);
// }

// void execute(t_data *data)
// {
//     int fd_in;
//     int saved_stdin;
//     int saved_stdout;

//     fd_in = 0;
//     if (ft_lstsize(data->list) == 1)
//         execute_one(data);
//     else
//     {
//         save_stdio(&saved_stdin, &saved_stdout);
//         while (data->list)
//         {
//             // if (data->list->limiter)
//             //     here_doc(data->list);
//             // ft_putnbr_fd(ft_lstsize(data->list),2);
//             // write(2,"-->\n", 4);

//             // // printf("%d\n", ft_lstsize(data->list));
//             // write(2, data->list->cmd_args[0], strlen(data->list->cmd_args[0]));
//             // printf("5\n");
//             // write(2, data->list->next->cmd_args[0], strlen(data->list->next->cmd_args[0]));
//             // printf("6\n");
//             execute_cmd(data, data->list, &fd_in);
//             data->list = data->list->next;
//         }
//         restore_stdio(saved_stdin, saved_stdout);
//         while (wait(NULL) > 0);
//     }
// }

// void execute(t_data *data)
// {
//     int pipe_fd[2];
//     int fd_in;
//     int saved_stdin;
//     int saved_stdout;

//     fd_in = 0;
//     save_stdio(&saved_stdin, &saved_stdout);
//     while (data->list)
//     {
//         if (data->list->next)
//             open_pipes(pipe_fd);
//         execute_cmd(data, data->list, fd_in, pipe_fd);
//         // printf("here\n");
//         if (data->list->next)
//         {
//             close(pipe_fd[1]);
//             if (fd_in != 0)
//                 close(fd_in);
//         }
//         fd_in = pipe_fd[0];
//         data->list = data->list->next;
//     }
//     while (wait(NULL) > 0);
//     restore_stdio(saved_stdin, saved_stdout);
// }
