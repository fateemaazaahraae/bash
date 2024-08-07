#ifndef MINISHELL
# define MINISHELL

# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "execution.h"
# include "parcing.h"
# include "env.h"

typedef struct s_global
{
    t_env   *my_env;
    char    *cmd;
    char    *pwd;
    int     exit_status;
    int     here_doc_nbr;
    bool    d_quote;
    bool    s_quote;
} t_global;

extern t_global *global_data;

#endif