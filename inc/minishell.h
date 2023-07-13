#ifndef MINISHELL_H
# define MINISHELL_H

//structures
typedef struct s_token
{
    int     index;
    int     error;
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
    PIPE,
    REDIRECT,
    APPEND,
    CMD,
    BUILTIN,
    WORD
};


//prototypes list
t_token	*ft_create_node(char *str);
void	ft_add_node_bottom(t_token **list, char *str);
void	ft_print_list(t_token *list);
void	ft_free_list(t_token **list);

//prototypes prompt
void ft_is_history(char *str);

//prototypes signal
void ft_handler(int signal);

//prototypes lexer
t_token *ft_lexer(char *str);

//prototypes lexer utils
int ft_is_blank(char c);
int ft_is_pipe_redir(char c);
int ft_single_quote(char *str, int i);
int ft_double_quote(char *str, int i);

//prototypes parser
int ft_count_pipes(t_token **list);
int ft_confirm_pipe(t_token **list);
int	ft_count_redirs(t_token **list);
int	ft_confirm_redir(t_token **list);
int ft_is_builtin(t_token **list);

//utils
int ft_strcmp(char *s1, char *s2);

#endif
