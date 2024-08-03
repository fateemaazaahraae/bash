/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:02:17 by aakouhar          #+#    #+#             */
/*   Updated: 2024/08/03 18:23:30 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int here_doc_vs_expand(int i)
{
    i -= 2;
    if (global_data->cmd[i] == ' ' && global_data->cmd[i - 1] == '<' && global_data->cmd[i - 2] == '<')
        return (1);
    return (0);
}

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
