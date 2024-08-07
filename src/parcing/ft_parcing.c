/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:11 by ali-akouhar       #+#    #+#             */
/*   Updated: 2024/08/07 16:14:08 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

/*filtre_1 check if there is a | in the end of our cmd and check
        if there is an unclosed quote*/
int filtre_1()
{
    int     i;

    i = 0;
    global_data->d_quote = false;
    global_data->s_quote = false;
    while (global_data->cmd[i])
    {
        if ((global_data->cmd[i] == '|' && global_data->cmd[i + 1] == '\0') || global_data->cmd[0] == '|')
            return (print_error('s', global_data->cmd[i])); 
        if (global_data->cmd[i] == '"' && !global_data->s_quote)
            global_data->d_quote = !global_data->d_quote;
        else if (global_data->cmd[i] == '\'' && !global_data->d_quote)
            global_data->s_quote = !global_data->s_quote;
        i++;
    }
    if (global_data->s_quote == true || global_data->d_quote == true)
        return (print_error('q', 'q'));
    return (0);
}

/* check if c is a special char : " <|>;&*(){}[]\t"*/
int is_special(char c, int flag)
{
    int i;
    char *check;

    check = " <|>;&*(){}#[]\t";
    if (flag == 1 && c == '"')
        return (1);
    else if (flag == 2 && c == '\'')
        return (1);
    else if (flag == 3 && (c == '\'' || c == '"'))
        return (1);
        
    i = -1;
    while (check[++i])
        if (check[i] == c)
            return (1);
    return (0);
}

/*slove_between_quote function if multiple all special_char by -1 as 
    '\'' or '"' or '|' etc (see function above)*/
void    solve_between_quote()
{
    int i;
    int flag;

    global_data->d_quote = false;
    global_data->s_quote = false;
    i = -1;
    while (global_data->cmd[++i])
    {
        if (global_data->cmd[i] == '"' && !global_data->s_quote)
        {
            global_data->d_quote = !global_data->d_quote;
            flag = 2;   
        }
        else if (global_data->cmd[i] == '\'' && !global_data->d_quote)
        {
            global_data->s_quote = !global_data->s_quote;
            flag = 1;   
        }
        if ((global_data->d_quote || global_data->s_quote) && is_special(global_data->cmd[i], flag))
            global_data->cmd[i] *= -1;
    }
}

/*new_cmd function add spaces and remove extra spaces ex : ls      -al ----> ls -al 
    and ls -al>p|cat p -----> ls -al > p | cat p */
char *new_cmd()
{
    int i;
    char *str;

    i = -1;
    str = NULL;
    if (!global_data->cmd)
        return (NULL);
    while (global_data->cmd[++i])
    {
        if (global_data->cmd[i] == ' ' && global_data->cmd[i + 1] == ' ')
            continue;
        if ((global_data->cmd[i] == '>' || global_data->cmd[i] == '<'))
            solve_here_doc(&i, &str);
        str = ft_strjoin_char(str, global_data->cmd[i]);  
    }
    str = ft_strjoin_char(str, '\0');
    free(global_data->cmd);
    return (str);
}

/*this function will filtre our input cmd to check syntax error*/
t_list *ft_filtre()
{
    global_data->cmd = ft_strtrim(global_data->cmd, " \t");
    if (filtre_1())
        return (NULL);
    solve_between_quote();
    global_data->cmd = new_cmd();
    if (!global_data->cmd)
        return (NULL);
    if (check_synthax())
        return (NULL);
    global_data->cmd = handle_expand();
    return (ft_fill_tokens());
}
