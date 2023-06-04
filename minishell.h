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
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//prototypes
void handler(int signal);

t_token *create_token(char *data);
t_token *parser(char *line);

#endif
