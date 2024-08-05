/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:52:08 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/04 15:10:59 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int is_builtins(char *command)
{
    return (!ft_strcmp(command, "cd") || 
            !ft_strcmp(command, "echo") ||
            !ft_strcmp(command, "pwd") ||
            !ft_strcmp(command, "export") ||
            !ft_strcmp(command, "unset") ||
            !ft_strcmp(command, "env") ||
            !ft_strcmp(command, "exit"));
}

void    execute_builtins(t_list *list)
{
    if (list->outfile > 1)
    {
        dup2(list->outfile, STDOUT_FILENO);
        close(list->outfile);
    }
    if (ft_strcmp(list->cmd_args[0], "cd") == 0) // done
        cd(list->cmd_args);
    else if (ft_strcmp(list->cmd_args[0], "echo") == 0) // done
        echo(list);
    else if (ft_strcmp(list->cmd_args[0], "pwd") == 0) // done
        pwd();
    else if (ft_strcmp(list->cmd_args[0], "export") == 0)
        export(list->cmd_args);
    else if (ft_strcmp(list->cmd_args[0], "unset") == 0)
        unset(list->cmd_args, global_data->my_env);
    else if (ft_strcmp(list->cmd_args[0], "env") == 0) // done
        env(list->cmd_args);
    else if (ft_strcmp(list->cmd_args[0], "exit") == 0)
        exit(0);
}
