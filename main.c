
#include "minishell.h"

int main(void)
{
    char *line;

    //ignore SIGQUIT Ctrl+|
    signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
    signal(SIGINT, &handler);
    while (1)
    {
        line = readline("> "); // Prompt 
        // Ctrl+D (EOF)
        if (!line) {
            write(2, "exit\n", 5);
            free(line);
            break ;
        }
        // cmd exit
        if (ft_strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
        // include readline/history.h
        //access - arrow-up
        add_history(line);
        //print_tokens(split(line));
        parser(line);
        //ft_split_to_array(line);
        //ft_split_to_tokens(line);
        //free user input
        free(line);
    }
    return 0;
}
