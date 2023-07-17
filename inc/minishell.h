#ifndef MINISHELL_H
# define MINISHELL_H

//structures
typedef struct s_token
{
    int     index;
    int     type;
    int     error_code;
    char    *data;
    struct s_token  *next;
}   t_token;

//includes
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

enum token_class 
{
    PIPE=1,
    REDIRECT_IN,
    REDIRECT_OUT,
    APPEND,
    HEREDOC,
    CMD,
    BUILTIN_ECHO,
    BUILTIN_CD,
    BUILTIN_PWD,
    BUILTIN_EXPORT,
    BUILTIN_UNSET,
    BUILTIN_ENV,
    BUILTIN_EXIT,
    WORD,
    EXPAND,
    ERR
};

//prototypes builtins - env
void ft_builtin_env(t_token *new_env);

//prototypes lexer utils quotes
int ft_single_quote(char *str, int i);
int ft_double_quote(char *str, int i);

//prototypes lexer utils
int ft_is_blank(char c);
int ft_is_pipe_redir(char c);
int	ft_is_pipe(char c);
int ft_is_redir_more(char c);
int ft_is_redir_less(char c);

//prototypes lexer
t_token *ft_lexer(char *str);


//prototype parser utils bultin
int ft_is_builtin(t_token **list);

//prototypes parser utils err
int	ft_err_pipe(t_token **list);
int	ft_err_redir_in(t_token **list);
int	ft_err_redir_out(t_token **list);

//prototypes parser utils redirs
int	ft_confirm_append(t_token **list);
int	ft_confirm_heredoc(t_token **list);
int	ft_confirm_redir_out(t_token **list);
int	ft_confirm_redir_in(t_token **list);

//prototypes parser utils
int ft_count_pipes(t_token **list);
int	ft_count_redirs(t_token **list);

//prototypes parser
int ft_confirm_pipe(t_token **list);

//prototypes expand
t_token *ft_copy_env(char **envp);
int ft_confirm_expand(t_token **list);
void ft_vars_to_expand(t_token **list);
int	ft_is_expand(char *data);

//prototypes list
t_token	*ft_create_node(char *str, int index);
void	ft_add_node_bottom(t_token **list, char *str, int index);
void	ft_print_list(t_token *list);
void	ft_free_list(t_token **list);

//prototypes prompt
void ft_is_history(char *str);

//prototypes signal
void ft_handler(int signal);

//utils
int ft_strcmp(char *s1, char *s2);

#endif
