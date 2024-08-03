/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:11 by ali-akouhar       #+#    #+#             */
/*   Updated: 2024/08/03 18:21:13 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int filtre_1()
{
    int     i;

    i = 0;
    global_data->d_quote = false;
    global_data->s_quote = false;
    while (global_data->cmd[i])
    {
        if ((global_data->cmd[i] == '|' && global_data->cmd[i + 1] == '\0') || global_data->cmd[0] == '|')
            return (print_error('s')); 
        if (global_data->cmd[i] == '"' && !global_data->s_quote)
            global_data->d_quote = !global_data->d_quote;
        else if (global_data->cmd[i] == '\'' && !global_data->d_quote)
            global_data->s_quote = !global_data->s_quote;
        i++;
    }
    if (global_data->s_quote == true || global_data->d_quote == true)
        return (print_error('s'));
    return (0);
}

int is_special(char c, int flag)
{
    int i;
    char *check;

    check = " <|>;&*(){}[]\t";
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
    // if (data->cmd[*i] != '\0')
    //     solve_here_doc(data, i, str, here_doc);
}

void    return_special_char(t_list *list)
{
    int i;
    int j;

    t_list *tmp;
    tmp = list;
    while (tmp) // ls -la |||| cat hello
    {
        i = -1;
    // printf("iiiiiii%d\n", list->i);
        while (tmp->mini_tokens[++i]) // ls -la
        {
            j = -1;
            while(tmp->mini_tokens[i][++j]) // l s - l a
            {
                if (is_special(tmp->mini_tokens[i][j] * (-1), 3))
                    tmp->mini_tokens[i][j] *= -1;
            }
        }
        tmp = tmp->next;   
    }
}

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
        if (global_data->cmd[i] == '"')
            continue;
        str = ft_strjoin_char(str, global_data->cmd[i]);  
    }
    str = ft_strjoin_char(str, '\0');
    free(global_data->cmd);
    return (str);
}

t_list *ft_filtre()
{
    global_data->cmd = ft_strtrim(global_data->cmd, " \t");
    if (filtre_1())
        return (NULL);
    solve_between_quote();
    global_data->cmd = new_cmd();
    if (!global_data->cmd)
        return (NULL);
    global_data->cmd = handle_expand();
    printf("--> cmd : %s\n", global_data->cmd);
    return (ft_fill_tokens());
}
