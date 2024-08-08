/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:10:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/08 12:50:49 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int    check_existence(char *cmd)
{
    DIR *dir;

    dir = opendir(cmd);
    if (dir)
    {
        global_data->exit_status = 126;
        exit_func(DIR_ERR, cmd);
        closedir(dir);
        exit(global_data->exit_status);
    }
    if (access(cmd, F_OK) == -1)
    {
        exit_func(NO_SUCH_FILE, cmd);
        global_data->exit_status = 127;
        exit(global_data->exit_status);
    }
    if (access(cmd, X_OK) == -1)
    {
        exit_func(PERR_DENIED, cmd);
        exit(global_data->exit_status);
    }
    return (0);
}

char *get_cmd_path(char *cmd, char **paths)
{
    int i;
    char *cmd_path;

    if (!cmd)
        return (NULL);
    if (!paths)
    {
        exit_func(NO_SUCH_FILE, cmd);
        global_data->exit_status = 127;
        exit(global_data->exit_status);
    }
    if (ft_strchr(cmd, '/'))
        if (!check_existence(cmd))
            return (cmd);
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
    char **cmd_args;
    char *cmd_path;

    global_data->exit_status = 0;
    all_path = find_path(global_data->my_env);
    paths = ft_split(all_path, ':');
    if (ft_strchr(list->cmd_args[0], '\n'))
        cmd_args = ft_split(list->cmd_args[0], '\n');
    else
        cmd_args = list->cmd_args;
    cmd_path = get_cmd_path(cmd_args[0], paths);
    if (!cmd_path)
    {
        exit_func(CMD_NOT_FOUND, list->cmd_args[0]);
        free(all_path);
        free_2D(paths);
        exit (global_data->exit_status);
    }
    execve(cmd_path, cmd_args, env_to_2D(global_data->my_env));
    exit_func(EXECVE, NULL);
}

