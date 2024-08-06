#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "env.h"

typedef enum s_error
{
    PIPE_ERR,
    FORK_ERR,
    ACCESS,
    CMD_NOT_FOUND,
    EXECVE,
    NUM_ARGS,
    CD_TOO_ARGS,
    HOME_NOT_SET,
    OLDPWD_NOT_SET,
    CHDIR,
    ENV_ERR,
    EXPORT_ERR,
    NO_SUCH_FILE,
    PERR_DENIED,
    AMBIGUOUS
}   t_error;


/* ----------------------BUILTINS------------------------ */
/* --echo.c-- */
int nb_args(char **args);
int echo(t_list *list);

/* --cd.c-- */
void cd(char **args);
void    update_old_pwd(t_env *env);
void    go_to_home(t_env *env);
void    update_pwd(t_env *env);

/* --pwd.c-- */
void    pwd();

/* --env.c-- */
void    env(char **args);

/* --unset.c-- */
void    unset_var(t_env **env, char *key);
void    unset(char **args);

/* --export.c-- */
void    export(char **args);
void	print_sorted_env(t_env *head);
void    lst_addexport(t_env **env, t_env *new);



/* ----------------------ENV------------------------ */
/* --get_env.c-- */
int	ft_lstsize2(t_env *lst);
t_env   *get_env(char **env);

/* --execution.c-- */
pid_t    fork_process();
void    open_pipes(int *pipe_fd);

/* --get_env_utils.c */
t_env	*ft_lstnew2(char *name, char *value);
t_env	*ft_lstlast2(t_env *lst);
void	ft_lstadd_back2(t_env **lst, t_env *new);
void	ft_lstdelone2(t_env *lst);
char	*find_key_env(char *key);

/* --env_to_2D.c-- */
char **env_to_2D(t_env *env);


/* ----------------------EXECUTION------------------------ */
/* --exec_builtin.c-- */
int is_builtins(char *command);
void    execute_builtins(t_list *list);

/* --exec_non_builtin.c-- */
char *find_path(t_env *my_env);
char *get_cmd_path(char *cmd, char **paths);
void    ft_execve(t_list *list);

/* --multi_pipe.c-- */
void here_doc(t_list *list);

/* --execution_tools.c-- */
void dup_out_pipe(t_list *list);
void save_stdio(int *saved_stdin, int *saved_stdout);
void restore_stdio(int saved_stdin, int saved_stdout);


/* --ft_free.c-- */
void    ft_free_struct(t_list **list);
void    free_2D(char **str);
void    ft_lstclear2(t_list **lst);

void    close_pipe(t_list *list, int i);
void    exit_func(t_error err, char *cmd);
void    execution(t_list *list);
void    run_execution(t_list *list);
int    execute_cmd(t_list *list);


void    ft_expand(int *i, char **str, char *line);
char    *expand_in_here_doc(char *line);
void here_doc(t_list *list);
int check_in(t_redir *infile);
int check_out(t_redir *outfile);
int open_files(t_list *list);
void    dup_infile(t_redir *infile);
void    dup_outfile(t_redir *outfile);
int	ft_is_alphanum(char *str);


#endif