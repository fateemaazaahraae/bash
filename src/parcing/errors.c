/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:13:31 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/06 16:33:22 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_oper(char c)
{
    char *oper;
    int i;
    
    oper = "><|";
    i = -1;
    while (oper[++i])
        if (c == oper[i])
            return (1);
    return (0);
}

int check_synthax()
{
    char *check;
    int i;
    int j;
 
    check = "*;()&";
    i = -1;
    while (global_data->cmd[++i])
    {
        if (global_data->cmd[i] == '|' && global_data->cmd[i + 1] == ' ' && is_oper(global_data->cmd[i + 2]))
            continue;
        if (is_oper(global_data->cmd[i]) && global_data->cmd[i + 1] == ' ' && is_oper(global_data->cmd[i + 2]))
            return (print_error('s', global_data->cmd[i + 2]), -1);
    }
    i = -1;
    while (global_data->cmd[++i])
    {
                    
        j = 0;
        while (check[j])
        {
            if (global_data->cmd[i] == check[j])
                return (print_error('s', global_data->cmd[i]), -1);
            j++;
        }
    }
    return (0);
}

int print_error(char c, char x)
{
    if (c == 's')
    {
        printf("minishell: syntax error near unexpected token `%c'\n", x);
        global_data->exit_status = 1;
    }
    else if (c == 'q')
    {
        printf("unclosed qoute\n");
        global_data->exit_status = 1;
    }
    return (global_data->exit_status);
}