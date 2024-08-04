/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:30 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/04 15:07:33 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    join_single_quote(int *i, char **str)
{
    if (global_data->cmd[*i] == '\'')
    {
        *str = ft_strjoin_char(*str, '\'');
        (*i)++;
    }
    while (global_data->cmd[*i] && global_data->cmd[*i] != '\'')
    {
        *str = ft_strjoin_char(*str, global_data->cmd[*i]);
        (*i)++;
    }
    if (global_data->cmd[*i] == '\'')
        *str = ft_strjoin_char(*str, '\'');
}

void    expand(int *i, char **str)
{
    int start;
    int end;
    char *s;

    if (here_doc_vs_expand(*i))
    {
        handle_here_doc_expand(i, str);
        return  ;
    }
    if (global_data->cmd[*i] == '?')
    {
        *str = ft_strjoin(*str, ft_itoa(global_data->exit_status));
        (*i)++;
        return ;
    }
    start = *i;
    while (ft_isalnum(global_data->cmd[*i]))
        (*i)++;
    end = *i;
    s = find_key_env(ft_substr(global_data->cmd, start, end - start));
    *str = ft_strjoin(*str, s);
    (*i)--;
}

char *handle_expand()
{
    int i;
    char *str;

    i = -1;
    str = NULL;
    while (global_data->cmd[++i])
    {
        if (global_data->cmd[i] == '\'')
            join_single_quote(&i, &str);
        else if (global_data->cmd[i] == '$' && global_data->cmd[i + 1] && global_data->cmd[i + 1] != ' ')
        {
            i++;
            expand(&i, &str);
        }
        else
            str = ft_strjoin_char(str, global_data->cmd[i]);
    }
    free(global_data->cmd);
    return (str);
}

char    *remove_quotes()
{
    int     i;
    char    *str;

    i = -1;
    str = NULL;
    while (global_data->cmd[++i])
    {
        if (global_data->cmd[i] == '"' || global_data->cmd[i] == '\'')
            continue ;
        str = ft_strjoin_char(str, global_data->cmd[i]);
    }
    free(global_data->cmd);
    return (str);
}
