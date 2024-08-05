/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:40:55 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/04 15:12:59 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

void	set_value_env(char *key, char *value)
{
	t_env	*env;

	env = global_data->my_env;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (env->value)
				free(env->value);
            env->value = "";
			env->value = ft_strjoin(env->value, value);
            return ;
		}
		env = env->next;
	}
}

char *new_cwd_env(char *str)
{
    char *path;

    path = NULL;
    if (!str || str[0] == '~')
    {
        path = find_key_env("HOME");
        if (!path)
        {
            global_data->exit_status = 1;
            exit_func(HOME_NOT_SET, NULL);
            return (NULL);
        }
    }
    else if (str[0] == '-')
    {
        path = find_key_env("OLDPWD");
        if (!path)
        {
            global_data->exit_status = 1;
            exit_func(OLDPWD_NOT_SET, NULL);
            return (NULL);
        }
    }
    if (!path)
        path = str;
    return (path);
}

void    handle_path(char *str)
{
    char *cwd;
    char *new_cwd;

    cwd = getcwd(NULL, 0);
    new_cwd = new_cwd_env(str);
    if (!new_cwd)
        return ;
    if (new_cwd && chdir(new_cwd) == -1)
    {
        global_data->exit_status = 1;
        exit_func(CHDIR, new_cwd);
        free(new_cwd);
    }
    set_value_env("OLDPWD", cwd);
    if (cwd)
        free(cwd);
    cwd = getcwd(NULL, 0);
    set_value_env("PWD", cwd);
    if (global_data->pwd)
        free(global_data->pwd);
    global_data->pwd = cwd;
    if (str && !ft_strcmp(str, "-"))
        pwd();
}


void cd(char **args)
{
    if (args[2])
    {
        exit_func(CD_TOO_ARGS, NULL);
        return ;
    }
    if (!args[1])
        args[1] = NULL;
    handle_path(args[1]);
}
