/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:29:38 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/31 19:03:42 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

void    print_env()
{
    t_env *env;

    env = global_data->my_env;
    while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
}

void    env(char **args)
{
    if (!args[1])
        print_env();
    else
    {
        global_data->exit_status = 127;
        exit_func(ENV_ERR, args[1]);
    }
}