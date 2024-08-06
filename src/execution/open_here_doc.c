/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:41:44 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 19:39:46 by fbazaz           ###   ########.fr       */
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

void here_doc(t_redir *node)
{
    char *line;
    
    // node->filename = generate_filename();
    node->filename = "_tmp";
    node->fd = open(node->filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    while (1)
    {
        line = readline("> ");
        if (!ft_strcmp(line, node->lim))
        {
            free(line);
            break ;
        }
        if (ft_strchr(line, '$'))
            line = expand_in_here_doc(line);
        ft_putendl_fd(line, node->fd);
        free(line);
    }
    close(node->fd);
}
