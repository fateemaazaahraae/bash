/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:16:28 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 14:54:44 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    run_execution(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp)
    {
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
}

void    execution(t_list *list)
{
    int stdin;
    int stdout;

    save_stdio(&stdin, &stdout);
    if (ft_lstsize(list) == 1 && is_builtins(list->cmd_args[0]))
    {
        if (open_files(list))
            return ;
        dup_outfile(list->out);
        execute_builtins(list);
        restore_stdio(stdin, stdout);
        return ;
    }
    run_execution(list);
    restore_stdio(stdin, stdout);
}
