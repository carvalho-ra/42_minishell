#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char	*line;
	t_token	*list;
	t_token *new_env;

	new_env = malloc(sizeof(t_token*));
	if (!new_env)
		return (1);
	new_env = ft_copy_env(envp);

	(void)argv;
	(void)argc;

    //ignore SIGQUIT Ctrl+'\'
    signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
    signal(SIGINT, &ft_handler);
    while (1)
    {
        line = readline("minishell> "); // Prompt 
		// Ctrl+D (EOF)
		if (!line) 
		{
			write(2, "exit\n", 5);
			//free user input
			if (!line)
				break ;
			else
				free(line);
			break ;
		}
		// cmd exit
		if (ft_strcmp(line, "exit") == 0)
		{
			//free user input
			free(line);
			break ;
		}
		if (ft_strcmp(line, "env") == 0)
		{
			//print env on call
			ft_builtin_env(new_env);
			continue ;
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

		ft_free_list(&list);
	}
	ft_free_list(&new_env);
	free(new_env);
    return (0);
}
