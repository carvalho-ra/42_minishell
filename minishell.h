#ifndef MINISHELL_H
# define MINISHELL_H

//structures
typedef struct s_token
{
    int index;
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

//prototypes
void handler(int signal);

t_token *create_token(char *data);
t_token *parser(char *line);

int ft_isblank(char c);
int ft_id_quotes(char *str, int i);
char    **ft_split_to_array(char *str);
void    print_arr_tokens(char **list_tokens);
t_token *ft_split_to_tokens(char *str);


t_token	*create_node(char *str);
void	add_node_bottom(t_token **list, char *str);
void    print_tokens(t_token *tokens_list);
t_token	*split(char *str);

//utils
int ft_strcmp(char *s1, char *s2);
t_token *tokenize(char *str);
void	print_list(t_token *list);
void	free_list(t_token **list);


#endif
