/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:17:20 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/30 16:32:45 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    handle_here_doc(t_list *tmp, int i)
{
    t_limiter *new;

    if (ft_lstsize_limiter(tmp->limiter) >= 16)
    {
        printf("minishell: maximum here-document count exceeded\n");
        exit(2);
    }
    if (!ft_strcmp(tmp->mini_tokens[i], "<<"))
    {
        new = ft_lstnew_limiter(tmp->mini_tokens[i + 1]);
        ft_lstadd_back_limiter(&tmp->limiter, new);
    }
    else if (((tmp->mini_tokens[i][0] == '>' || tmp->mini_tokens[i][0] == '<') && !tmp->mini_tokens[i][1]) || !ft_strcmp(tmp->mini_tokens[i], ">>"))
        handle_input_output(tmp, tmp->mini_tokens, i);
}

void    handle_input_output(t_list *tmp, char **args, int i)
{
    t_redir *new_redir;

    if (args[i][0] == '>')
    {
        if ((args[i][0] == '>' && !args[i][1]))
            new_redir = ft_lstnew_redir(args[i + 1], 1); // OUTPUT >
        else
            new_redir = ft_lstnew_redir(args[i + 1], 2); // APPEND >>
        ft_lstadd_back_redir(&tmp->out, new_redir);
    }
    else if (args[i][0] == '<' && !args[i][1])
    {
        new_redir = ft_lstnew_redir(args[i + 1], 3); // INPUT <
        ft_lstadd_back_redir(&tmp->in, new_redir);
    }
}
// ls <f1 -a >f2 -l>f3 | cat >> f4 -e >f5 | rm << hh -r << hhh > f6 -f