/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:38:00 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/05 11:12:30 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*this fuction count cmd + the number of its args to allocate memory for cmd_args*/
static int count_args(char **mini_tokens)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (mini_tokens[i])
    {
        if (mini_tokens[i][0] == '>' || mini_tokens[i][0] == '<')
            i += 2;
        else
        {
            len++;
            i++;
        }
    }
    return (len);
}

/*this function check if there if > or < it will go to handle redirection else it store the 
    args in cmd_args*/
static void    handle_args_and_redir(t_list *tmp)
{
    int     i;
    int     j;
    i = 0;
    j = 0;
    while (tmp->mini_tokens[i])
    {
        if (tmp->mini_tokens[i][0] == '>' || tmp->mini_tokens[i][0] == '<')
        {
            handle_here_doc(tmp, i);
            i += 2;  
        }
        else
        {
            tmp->cmd_args[j] = ft_strdup(tmp->mini_tokens[i]);
            j++;
            i++;
        }
    }
    tmp->cmd_args[j] = NULL;
}

/*this function fill cmd_args ex ls -a > p -l --> cmd_args[][] = {"ls", "-a", "-l", NULL}
    so it store the cnd and its args in cmd_args and it create a linked list of files*/
void    fill_cmd_args(t_list *list)
{
    int     count;
    t_list  *tmp;

    tmp = list;
    while (tmp)
    {
        count = count_args(tmp->mini_tokens);
        tmp->cmd_args = malloc(sizeof(char *) * (count + 1));
        if (!tmp->cmd_args)
        {
            printf("Error while allocating tmp->cmd_args\n");
            return ;
        }
        tmp->infile = 0;
        tmp->outfile = 1;
        handle_args_and_redir(tmp);
        tmp = tmp->next;
    }
}
