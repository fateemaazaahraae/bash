/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:17:20 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/06 11:28:50 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*this function check if there is << it will handle here doc it create a linked
    list of limiters else so we have input or output file*/
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

/*this fucntion check if there if > it open file with O_TRUNC flag and add it 
    to the linked list (out) else ">>" it open file with O_APPEND flag and add it
    else we have < so it open the file O_RDONLY and add it to the linked list (in)*/
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

/* solve the problem of space before or after the redir symbol 
    ex ls>p ---> ls > p or ls<<o ---> ls << o so it add spaces if needed*/
void solve_here_doc(int *i, char **str)
{
    if (global_data->cmd[*i] == '<' || global_data->cmd[*i] == '>')
    {
        if ((*i) > 0 && global_data->cmd[(*i) - 1] != ' ')
            *str = ft_strjoin_char(*str, ' ');
        *str = ft_strjoin_char(*str, global_data->cmd[*i]);
        if (global_data->cmd[*i + 1] == global_data->cmd[*i])
        {
            (*i)++;
            *str = ft_strjoin_char(*str, global_data->cmd[*i]);
        }
        if (global_data->cmd[*i + 1] != ' ' && global_data->cmd[*i + 1] != '\0')
            *str = ft_strjoin_char(*str, ' ');
    }
    else
        *str = ft_strjoin_char(*str, global_data->cmd[*i]);
    (*i)++;
}
