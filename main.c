
#include "minishell.h"

int main() {
    char* input;
    
    //ignore SIGQUIT Ctrl+|
    signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
    signal(SIGINT, &handler);
    
    while (1) {
        input = readline("> "); // Prompt 
        
        // Ctrl+D (EOF)
        if (!input) {
            printf("exit\n");
            free(input);
            break;
        }
        // cmd exit
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        // include readline/history.h
        //access - arrow-up
        add_history(input);
        
        free(input);
    }

    return 0;
}
