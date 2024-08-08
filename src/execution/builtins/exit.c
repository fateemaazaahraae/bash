/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:30:57 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/08 14:45:19 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

int len_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

void    ft_exit(char **args)
{
    int count;

    ft_putendl_fd("exit", STDERR_FILENO);
    if (!args[1])
        exit(global_data->exit_status);
    else
    {
        count = len_args(args);
        if (count > 2 && ft_isdigit(ft_atoi(args[1])))
        {
            exit_func()
        }
    }
}