/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:40:55 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/31 09:54:50 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

// void    update_old_pwd(t_env *env)
// {
//     char o_pwd[1000];

//     while (env)
//     {
//         if (!ft_strcmp(env->key, "OLDPWD"))
//         {
//             if (getcwd(o_pwd, sizeof(o_pwd)))
//             {
//                 free(env->value);
//                 env->value = ft_strdup(o_pwd);
//             }
//                 // ft_strcpy(env->value, o_pwd);
//             else
//                 perror("getcwd");
//             // printf(">> old_pwd: %s\n\n", env->value);
//             return ;
//         }
//         env = env->next;
//     }
// }

// void    update_pwd(t_env *env)
// {
//     char pwd[1000];

//     while (env)
//     {
//         if (!ft_strcmp(env->key, "PWD"))
//         {
//             if (getcwd(pwd, sizeof(pwd)))
//             {
//                 free(env->value);
//                 env->value = ft_strdup(pwd);
//             }
//             else
//                 perror("getcwd");
//             return ;
//         }
//         env = env->next;
//     }
// }

// void    go_to_home(t_env *env)
// {
//     while (env)
//     {
//         if (!ft_strcmp(env->key, "HOME"))
//         {
//             if (chdir(env->value))
//                 perror("cd");
//             return ;
//         }
//         env = env->next;
//     }
// }

// void    cd(char **args, t_env *env)
// {
//     update_old_pwd(env);
//     if (!args[1] || !ft_strcmp(args[1], "~"))
//         go_to_home(env);
//     else 
//         if (chdir(args[1]))
//             perror("cd");
//     update_pwd(env);
// }



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
