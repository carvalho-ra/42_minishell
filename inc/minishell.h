#ifndef MINISHELL_H
# define MINISHELL_H

//structures
typedef struct s_token
{
    int             index;
    int             type;
    int             error_code;
    char            *str;
    struct t_shell  *shell;
    struct s_token  *next;
}   t_token;

//AO FAZER NOVA STRUCT PARA MINISHELL

typedef struct s_shell
{
    char    *line; //chamar direto da readline pra cá
    char    *expanded;
    t_token *list;
    t_token *new_env;
}   t_shell;

//fazer função para repassar a lista (excluir nó do meio e dar free!!!)
// passar head + posição (INDEX)

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
void ft_builtin_env(t_shell *shell);

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
t_token *ft_lexer(t_shell *shell);

//prototype parser utils bultin
int ft_is_builtin(t_shell *shell);

//prototypes parser utils err
int	ft_err_pipe(t_shell *shell);
int	ft_err_redir_in(t_shell *shell);
int	ft_err_redir_out(t_shell *shell);

//prototypes parser utils redirs
int	ft_confirm_append(t_shell *shell);
int	ft_confirm_heredoc(t_shell *shell);
int	ft_confirm_redir_out(t_shell *shell);
int	ft_confirm_redir_in(t_shell *shell);

//prototypes parser utils
int ft_count_pipes(t_shell *shell);
int	ft_count_redirs(t_shell *shell);

//prototypes parser
int ft_confirm_pipe(t_shell *shell);

//prototypes expand
int ft_copy_env(t_shell *shell, char **envp);
int ft_confirm_expand(t_shell *shell);
void ft_vars_to_expand(t_shell *shell);
int	ft_is_expand(char *data, t_shell *shell);
char *ft_prep_expand(char *data);
char	*ft_look_for_in_env(char *str, t_shell *shell);

//prototypes list
t_token	*ft_create_node(char *str, int index);
void	ft_add_token(t_shell *shell, char *str, int index);
void	ft_add_env(t_shell *shell, char *str, int index);
void	ft_print_list(t_shell *shell);
void	ft_free_token_list(t_shell *shell);
void	ft_free_env_list(t_shell *shell);
void	ft_free_shell(t_shell *shell);


//prototypes prompt
void ft_is_history(char *str);

//prototypes signal
void ft_handler(int signal);

//utils
int ft_strcmp(char *s1, char *s2);

#endif
