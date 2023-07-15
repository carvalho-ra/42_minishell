#include "../inc/minishell.h"

//TODO need to export more than 1 variable at the same time? in the same line

// ler regras do export (man) 

// ler regras variaveis shell

//unset em variavel inexistente é igual ao comportamento normal, não dá erro

t_token *ft_copy_env(char **envp)
{
	t_token	*new_env;
	int		i;
	
	new_env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_add_node_bottom(&new_env, ft_strdup((const char *)envp[i]), 2);
		i++;
	}
	return (new_env);
}

