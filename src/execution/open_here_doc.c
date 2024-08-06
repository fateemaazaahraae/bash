/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:41:44 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 15:00:31 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    ft_expand(int *i, char **str, char *line)
{
    int start;
    int end;

    start = *i;
    while (ft_isalnum(line[*i]))
        (*i)++;
    end = *i;
    *str = ft_strjoin(*str, find_key_env(ft_substr(line, start, end - start)));
    (*i)--;
}

char    *expand_in_here_doc(char *line)
{
    int     i;
    char    *str;

    i = -1;
    str = NULL;
    while (line[++i])
    {
        if (line[i] == '$')
        {
            i++;
            ft_expand(&i, &str, line);
        }
        else
            str = ft_strjoin_char(str, line[i]);
    }
    free(line);
    return (str);
}

void here_doc(t_list *tmp)
{
    char *line;
    t_limiter *delimiter;

    delimiter = tmp->limiter;
    while (delimiter)
    {
        open_pipes(tmp->heredoc_fd);
        while ((line = readline("> ")) != NULL)
        {
            if (!ft_strcmp(line, delimiter->lim))
            {
                free(line);
                break;
            }
            if (ft_strchr(line, '$'))
                line = expand_in_here_doc(line);
            ft_putendl_fd(line, tmp->heredoc_fd[1]);
            free(line);
        }
        dup2(tmp->heredoc_fd[0], STDIN_FILENO);
        close_pipe(tmp, 1);
        delimiter = delimiter->next;
    }
}
