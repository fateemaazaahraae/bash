/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:30 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/03 18:21:06 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    join_single_quote(int *i, char **str)
{
    while (global_data->cmd[*i] && global_data->cmd[*i] != '\'')
    {
        *str = ft_strjoin_char(*str, global_data->cmd[*i]);
        (*i)++;
    }
    // (*i)++;
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
        {
            i++;
            join_single_quote(&i, &str);
        }
        else if (global_data->cmd[i] == '$' && global_data->cmd[i + 1] && global_data->cmd[i + i] != ' ')
        {
            i++;
            expand(&i, &str);
        }
        // else if (global_data->cmd[i] == '"')
        //     continue;
        else
            str = ft_strjoin_char(str, global_data->cmd[i]);
    }
    free(global_data->cmd);
    return (str);
}