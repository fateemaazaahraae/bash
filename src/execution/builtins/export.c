/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:28:02 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/31 19:39:41 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

int	ft_is_alphanum(char *str)
{
	int	i;

	i = -1;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

void    get_node(t_env *new, char *s)
{
    char *str;

    str = ft_strchr(s, '=');
    if (!str)
    {
        new->op = 'n';
        new->key = ft_strdup(s);
        new->value = NULL;
    }
    else
    {
        new->value = ft_strdup(str + 1);
        if (*(str - 1) == '+')
        {
            new->op = '+';
            new->key = ft_substr(s, 0 , str - 1 - s);
        }
        else
        {
            new->op = '=';
            new->key = ft_substr(s, 0, str - s);
        }
    }
}

t_env   *get_new(char *str)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    get_node(new, str);
    if (!ft_is_alphanum(new->key))
    {
        exit_func(EXPORT_ERR, new->key);
        free(new->key);
        free(new->value);
        free(new);
        global_data->exit_status = 1;
        return (NULL);
    }
    new->next = NULL;
    return (new);
}

void    export(char **args)
{
    int i;

    i = 0;
    if (!args[1])
    {
        print_sorted_env(global_data->my_env);
        return ;
    }
    while (args[++i])
    {
        if (args[i] && args[i][0] != '_' && !ft_isalpha(args[i][0]))
        {
            global_data->exit_status = 1;
            exit_func(EXPORT_ERR, args[i]);
            continue;
        }
        if (args[i])
            lst_addexport(&global_data->my_env, get_new(args[i]));
    }
}
