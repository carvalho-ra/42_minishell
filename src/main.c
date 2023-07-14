#include "../inc/minishell.h"

int main(void) //(int argc, char **argv, char **envp)
{
    char *line;
	t_token *list;
    
    //ignore SIGQUIT Ctrl+'\'
    signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
    signal(SIGINT, &ft_handler);
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

		list = ft_lexer(line);
		//table = parser(list);
		ft_print_list(list);

		ft_confirm_pipe(&list);
		ft_confirm_redir(&list);
		ft_confirm_expand(&list);
		ft_is_builtin(&list);
		printf("\n");

        //free user input
		free(line);
		//free list
		ft_free_list(&list);
	}
    return (0);
}
