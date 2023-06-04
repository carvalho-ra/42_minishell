#ifndef MINISHELL_H
# define MINISHELL_H

//includes
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//prototypes
void handler(int signal);

#endif
