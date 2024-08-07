/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:02:17 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/06 12:05:55 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*this function check if we have << before the $ => we have expand as limiter which should
    not expand*/
int here_doc_vs_expand(int i)
{
    i -= 2;
    if (global_data->cmd[i] == ' ' && global_data->cmd[i - 1] == '<' && global_data->cmd[i - 2] == '<')
        return (1);
    return (0);
}

/*this fucntion if the expand is limiter it hold it as it is and join it with str*/
void    handle_here_doc_expand(int *i, char **str)
{
    int start;
    int end;

    (*i)--;
    start = *i;
    while (global_data->cmd[*i] != ' ')
        (*i)++;
    end = *i;
    *str = ft_strjoin(*str, ft_substr(global_data->cmd, start, end - start));
}

void handle_ambigous(int start, int end, char **str)
{
    if ((global_data->cmd[start - 2] == '>' || global_data->cmd[start - 2] == '<') && global_data->cmd[start - 3] != '<')
        *str = ft_strjoin(*str, ft_substr(global_data->cmd, start, end - start));
}

