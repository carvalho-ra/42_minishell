#include "minishell.h"

void check_history(char *str)
{
    char    *tmp;

    tmp = ft_strtrim(str, " ");
    if (ft_strlen(tmp) == 0)
        add_history(str);
}


//include modifications in add_history
//add_history cannot take "nothing", just "enter"
//recheck with Will Branner


/*
int main(int argc, char **argv, char **envp)
{
    char *line;
	t_token *list;
    // char	*tmp0;
    // char	*tmp1;
    
    //ignore SIGQUIT Ctrl+|
    signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
    signal(SIGINT, &handler);
    while (1)
    {
        line = readline("minishell> "); // Prompt 
	// tmp0 = ft_strdup(line);
	// tmp1 = ft_strtrim(tmp0, " ");
	// if (ft_strlen(tmp1) != 0)
	// {
			// Ctrl+D (EOF)
			if (!line) {
        	    write(2, "exit\n", 5);
				//free(tmp0);
				//free(tmp1);
				free(line);
				break ;
        	}
	        // cmd exit
        	if (ft_strcmp(line, "exit") == 0)
        	{
            	free(line);
				// free(tmp0);
				// free(tmp1);
            	break;
        	}
        // include readline/history.h
        	add_history(line);
			list = tokenize(line);
		print_list(list);

        //free user input
		free(line);
		free_list(&list);
	}
	// free(tmp0);
	// free(tmp1);
    // }
    return (0);
}
*/