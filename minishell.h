#ifndef MINISHELL_H
# define MINISHELL_H

//structures
typedef struct s_token
{
    int     index;
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

//prototypes tokenization
int ft_isblank(char c);
int is_pipe_redir(char c);
int single_quote(char *str, int i);
int double_quote(char *str, int i);
t_token *tokenize(char *str);

//utils
int ft_strcmp(char *s1, char *s2);

#endif
