/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:01:38 by aakouhar          #+#    #+#             */
/*   Updated: 2024/07/18 18:37:57 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* //in this function i check if there is any pipe into a ' or " and multiple it in -1 andd check for synthax error
int    solve_pipe_problem(t_data *data)
{
    int i;
    
    i = -1;
    data->d_quote = false;
    data->s_quote = false;
    while (data->cmd[++i])
    { 
        if (data->cmd[i] == '\"')
            data->d_quote = !data->d_quote;
        else if (data->cmd[i] == '\'')
            data->s_quote = !data->s_quote;
        else if (data->cmd[i] == '|' && (data->s_quote || data->d_quote))
            data->cmd[i] *= -1;
        else if (data->cmd[i] == '|' && data->cmd[i + 1] == '|' && !data->s_quote && !data->d_quote)
            return (print_error(data, 's'));
    }
    if (data->s_quote == true || data->d_quote == true)
        return (print_error(data, 's'));
    return (check_synthax_error(data->cmd));
}
   
int is_error(char c)
{
    int i;
    char *find;
    
    find = "()&*;";
    i = -1;
    while (find[++i])
        if (find[i] == c)
            return (1);
    return (0);
}

int check_quote(t_data *data)
{
    int     i;

    i = -1;
    data->d_quote = false;
    data->s_quote = false;
    while (data->cmd[++i])
    {
        if (data->cmd[i] == '"' && !data->s_quote)
            data->d_quote = !data->d_quote;
        else if (data->cmd[i] == '\'' && !data->d_quote)
            data->s_quote = !data->s_quote;
    }
    if (data->s_quote == true || data->d_quote == true)
        return (print_error(data, 's'));
    return (0);
}

//check for simple synthax error
int check_synthax_error(t_data *data)
{
    int     i;

    i = -1;
    while (data->cmd[++i])
    {
        if (is_error(data->cmd[i]))
            return (print_error(data, 's'));
        if (data->cmd[i] == '>' && data->cmd[i + 1] == '<')
            return (print_error(data,'s'));
        else if ((data->cmd[i] == '>' || data->cmd[i] == '<') && (data->cmd[i + 1] == '|'))
            return (print_error(data, 's'));
        if (data->cmd[i] == '|' && (!is_all_space(data->cmd + i) || i == 0 || data->cmd[i + 1] == '|'))
            return (print_error(data, 's'));
    }
    return (check_quote(data));
}

int is_all_space(char *str)
{
    int i;

    i = 1;
    while (str[i] == ' ')
        i++;
    if (str[i])
        return (1);
    return (0);
} */

