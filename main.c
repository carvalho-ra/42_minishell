
#include "minishell.h"

int main() {
    char* line;
    
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
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
        // include readline/history.h
        //access - arrow-up
        add_history(line);

        parser(line);
        
        //free user input
        free(line);
    }

    return 0;
}
