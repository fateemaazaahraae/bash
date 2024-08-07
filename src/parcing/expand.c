/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:29:30 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/07 10:39:21 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*join_single_quote function joing all things inside single quote
    because we don't expand inside the single quote so we have to ignore
    it and it join it in str (the string we will return)*/
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

/*expand function simply it expand the vars but in here_doc if the expand
    is limiter we don't expand it so we check it first then we continue
    we check if we have $? if yes we replace it with the last exit status
    if no we take the string after $ and we seach in env for it if we found
    it we replace the key by it value if not we just do nothing*/
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

/* handle_expand function will expand the vars and free the global_data->cmd and return the new one*/
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

/* after expand we remove the master quote ex : echo "'hello'" ----> echo 'hello'*/
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
