#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handler(int signal)
{
    //use write on fd = 2?
    write(2, "\n", 1);
	if (signal == SIGINT)
	{
        //move cursor down 1 line
		rl_on_new_line ();
        //replace the line by (no char "", 0)
		rl_replace_line ("", 0);
        //make sure readline will exibit entry
		rl_redisplay ();
	}
}

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
            write (2, "exit\n", 5);
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
