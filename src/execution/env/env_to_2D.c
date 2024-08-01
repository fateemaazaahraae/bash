/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_2D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:16:37 by tiima             #+#    #+#             */
/*   Updated: 2024/07/17 17:27:54 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

char **env_to_2D(t_env *env)
{
    char **env_2D;
    int i;
    
    env_2D = malloc(sizeof(char *) * (ft_lstsize2(env) + 1));
    if (!env_2D)
        return (printf("Error while allocate memory for env_2D\n"), NULL);
    i = 0;
    while (env)
    {
        env_2D[i] = ft_strdup(env->key);
        env_2D[i] = ft_strjoin(env_2D[i], "=");
        env_2D[i] = ft_strjoin(env_2D[i], env->value);
        i++;
        env = env->next;
    }
    env_2D[i] = NULL;
    return (env_2D);
}