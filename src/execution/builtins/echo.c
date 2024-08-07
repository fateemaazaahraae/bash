/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:37:08 by tiima             #+#    #+#             */
/*   Updated: 2024/08/07 20:07:40 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

int nb_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

int is_n_flag(char *arg)
{
    int j = 1;
    if (arg[0] != '-')
        return (0);
    while (arg[j]) {
        if (arg[j] != 'n')
            return (0);
        j++;
    }
    return (1);
}

int echo(t_list *list)
{
    int i;
    int n_flag;
    
    i = 1;
    n_flag = 0;
    while (list->cmd_args[i] && is_n_flag(list->cmd_args[i]))
    {
        n_flag = 1;
        i++;
    }
    while (list->cmd_args[i])
    {
        printf("%s", list->cmd_args[i]);
        if (list->cmd_args[i + 1])
            printf(" ");
        i++;
    }
    if (!n_flag)
        printf("\n");
    global_data->exit_status = 0;
    return (0);
}

