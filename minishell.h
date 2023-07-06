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

//prototypes history
void is_history(char *str);

//prototypes list
t_token	*create_node(char *str);
void	add_node_bottom(t_token **list, char *str);
void	print_list(t_token *list);
void	free_list(t_token **list);

//prototypes prompt
void check_history(char *str);

//prototypes signal
void handler(int signal);

//prototypes lexer
int ft_isblank(char c);
int is_pipe_redir(char c);
int single_quote(char *str, int i);
int double_quote(char *str, int i);
t_token *lexer(char *str);

//prototypes parser
int count_pipes(t_token **list);
int confirm_pipe(t_token **list);
int	count_redirs(t_token **list);
int	confirm_redir(t_token **list);
int is_builtin(t_token **list);

//utils
int ft_strcmp(char *s1, char *s2);

#endif
