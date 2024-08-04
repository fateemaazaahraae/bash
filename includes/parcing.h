#ifndef PARCING_H
# define PARCING_H
 
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include "../libft/libft.h"

/* -------------------------------PARCING--------------------------------*/
void split_tokens(t_list **p_tokens);
t_list    *ft_fill_tokens();
void fill_mini_tokens(t_list *list);

int print_error(char c);
void    ft_free_struct(t_list **list); 

void    solve_pipe_problem(char *str);
void    solve_between_quote();
int check_synthax_error(char *str);
int is_all_space(char *str);
void    check_pipe(char *str, char *check);
t_list *ft_filtre();
int filtre_1();
char *new_cmd();
// void solve_rederction_problem(t_data *data, int *i, char *str);
char	*ft_strjoin_char(char const *s1, char c);
void    return_special_char(t_list *list);
void    fill_cmd_args(t_list *list);
void    handle_here_doc(t_list *tmp, int i);
int last_here_doc(char **args, int i);
void    handle_input_output(t_list *tmp, char **args, int i);
void ft_lstadd_back_redir(t_redir **redir, t_redir *new);
t_redir	*ft_lstlast_redir(t_redir *redir);
t_redir	*ft_lstnew_redir(char *name, int flag);
void ft_lstclear_redir(t_redir **lst);

void ft_lstclear_limiter(t_limiter **lst);
t_limiter	*ft_lstnew_limiter(char *name);
t_limiter	*ft_lstlast_limiter(t_limiter *limiter);
void ft_lstadd_back_limiter(t_limiter **limiter, t_limiter *new);
int	ft_lstsize_limiter(t_limiter *lim);
void    expand(int *i, char **str);
void    join_single_quote(int *i, char **str);
char *handle_expand();
void    handle_here_doc_expand(int *i, char **str);
int here_doc_vs_expand(int i);
void check_files(t_list *list);
int check_out(t_list *tmp);
int check_in(t_list *tmp);
char    *remove_quotes();
int init_program(char **av, int ac, char **envp);

#endif