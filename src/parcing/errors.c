/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:13:31 by aakouhar          #+#    #+#             */
/*   Updated: 2024/07/30 15:01:50 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_error(char c)
{
    if (c == 's')
    {
        printf("synthax error\n");
        global_data->exit_status = 1;
    }
    return (global_data->exit_status);
}