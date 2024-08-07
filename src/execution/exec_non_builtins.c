/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:10:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/07 14:53:47 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char *get_cmd_path(char *cmd, char **paths)
{
    int i;
    char *cmd_path;

    if (!cmd || !paths)
        return (NULL);
    if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
        {
			printf("minishell : %s: No such file or directory\n", cmd);
            exit(127);
        }
	}
    i = -1;
    while (paths[++i])
    {
        cmd_path = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(cmd_path, cmd);
        if (!access(cmd_path, X_OK))
            return (cmd_path);
        free(cmd_path);
    }
    return (NULL);
}

char *find_path(t_env *my_env)
{
    t_env *env;

    env = my_env;
    while (env)
    {
        if (!ft_strcmp(env->key, "PATH"))
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (NULL);
}

void    ft_execve(t_list *list)
{
    char *all_path;
    char **paths;
    char *cmd_path;

    all_path = find_path(global_data->my_env);
    paths = ft_split(all_path, ':');
    cmd_path = get_cmd_path(list->cmd_args[0], paths);
    if (!cmd_path)
    {
        exit_func(CMD_NOT_FOUND, list->cmd_args[0]);
        free(all_path);
        free_2D(paths);
        exit (127);
    }
    // printf("allaho akbar\n");
    execve(cmd_path, list->cmd_args, env_to_2D(global_data->my_env));
    exit_func(EXECVE, NULL);
}

