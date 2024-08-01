/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:11:04 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/31 09:54:48 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

void    pwd()
{
    char *path;

    path = getcwd(NULL, 0);
    if (!path)
        path = global_data->pwd;
    printf("%s\n", path);
    if (path != global_data->pwd)
        free(path);
}