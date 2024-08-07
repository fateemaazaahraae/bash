/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakouhar <aakouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:40:49 by tiima             #+#    #+#             */
/*   Updated: 2024/08/06 20:33:24 by aakouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"
// # include "../includes/parcing.h"

t_global *global_data = NULL;

int init_program(char **av, int ac, char **envp)
{
    (void)av;
    (void)envp;
    global_data = malloc(sizeof(t_global));
    global_data->my_env = get_env(envp);
    global_data->exit_status = 0;
    global_data->pwd = NULL;
    if (ac != 1)
    {
       exit_func(NUM_ARGS, av[1]);
       exit(EXIT_FAILURE); 
    }
    return (0);
}

void    ft_handler(int x)
{
    if (x == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
        global_data->exit_status = 130;
    }
    else if (x == SIGQUIT)
        return ;
}
void ft_after(int num)
{
    if (num == SIGINT)
        global_data->exit_status = 130;
}
int main(int ac, char **av, char **env)
{
    t_list  *list;

    init_program(av, ac, env);
    while (1)
    {
        signal(SIGINT, &ft_handler);
        global_data->cmd = readline("\x1b[36mminishell $> \x1b[0m");
        signal(SIGINT, &ft_after);
        if (!global_data->cmd)
        {
            printf("exittttttttttttt\n");
            exit(0);
        }
        add_history(global_data->cmd);
        list = ft_filtre();
        if (!list)
        {
            free(global_data->cmd);
            continue;
        }
        execution(list);
        // ft_free_struct(&list);
    }
    return (global_data->exit_status);
}
