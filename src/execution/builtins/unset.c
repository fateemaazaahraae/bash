/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:41:31 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/21 16:13:29 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

void    unset_var(t_env **env, char *key)
{
    t_env   *current;
    t_env   *previous;

    current = *env;
    previous = NULL;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
        {
            if (previous)
                previous->next = current->next;
            else
                *env = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return ;
        }
        previous = current;
        current = current->next;
    }
}

void    unset(char **args, t_env *env)
{
    int i;

    i = 1;
    if (!args[i])
        return ;
    while (args[i])
    {
        unset_var(&env, args[i]);
        i++;
    }
}
