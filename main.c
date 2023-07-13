#include "minishell.h"

int main(void) //(int argc, char **argv, char **envp)
{
    char *line;
	t_token *list;
    
    //ignore SIGQUIT Ctrl+'\'
    signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
    signal(SIGINT, &handler);
    while (1)
    {
        line = readline("minishell> "); // Prompt 
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
		ft_is_history(line);

		list = lexer(line);
		//table = parser(list);
		print_list(list);
		//printf("count pipes: %i\n", count_pipes(&list));
		confirm_pipe(&list);
		//printf("count redirects: %i\n", count_redirs(&list));
		confirm_redir(&list);
		is_builtin(&list);

        //free user input
		free(line);
		//free list
		free_list(&list);
	}
    return (0);
}
