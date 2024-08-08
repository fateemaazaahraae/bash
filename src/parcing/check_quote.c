/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:42:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/08 18:11:32 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    handle_quote(char *token, int *j, char **str)
{
    int start;
    int end;

    (*j)++;
    start = *j;
    while (token[*j] && token[*j] != '\'' && token[*j] != '"')
        (*j)++;
    end = *j;
    *str = ft_strjoin(*str, ft_substr(token, start, end - start));
}

/* after expand we remove the master quote ex : echo "'hello'" ----> echo 'hello'*/
void    remove_quotes(t_list *tmp)
{
    int     i;
    int     j;
    char    *str;
    t_list  *list;

    list = tmp;
    while (list)
    {
        i = -1;
        while (list->mini_tokens[++i])
        {
            j = -1;
            str = NULL;
            while (list->mini_tokens[i][++j])
            {
                if (list->mini_tokens[i][j] == '\'' || list->mini_tokens[i][j] == '"')
                    handle_quote(list->mini_tokens[i], &j, &str);
                else
                    str = ft_strjoin_char(str, list->mini_tokens[i][j]);
            }
            free(list->mini_tokens[i]);
            list->mini_tokens[i] = str;
            if (!ft_strcmp(list->mini_tokens[i], "<<"))
                i++;
        }
        list = list->next;
    }
}

char *remove_quote_from_lim(char *name, int *lim_flag)
{
    char    *str;
    int     i;

    str = NULL;
    i = -1;
    *lim_flag = 1;
    while (name[++i])
    {
        if (name[i] == '"' || name[i] == '\'')
            continue;
        else
            str = ft_strjoin_char(str, name[i]);
    }
    free(name);
    i = -1;
    while (str[++i])
    {
        if (is_special(str[i] * (-1), 0) || str[i] * (-1) == '\'' || str[i] * (-1) == '"')
            str[i] *= -1;
    }
    return (str);
}
