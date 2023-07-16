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

// pseudocode

// look for expand ($)
// - function to iterate through strings looking for $ (ISSUE! consider $$???)
// - iterate and do it in each node  

int ft_count_expands(char *str)
{
	int	i;
	int	flag;
	int	count;

	while (str[i])
	{
		i = 0;
		flag = 0;
		while (str[i])
		{
			//TODO
			//ISSUE!! if there's more than one expands in the word must expand
			// preciso dormir .....
			if (str[i] == '$' && str[i + 1])
			{
				flag = 1;
				i++;
				while (str[i++] == '$')
					flag++;
				if (flag <= 2)
				{
					count++;
					printf("is expand %i\n", flag);
				}
			}
			i++;
		}
	}
	return (count);
}

// pseudocode

// look for expand ($)
// - function to iterate through strings
// of each node looking for $ (ISSUE! consider $$???)

int ft_confirm_expand(t_token **list)
{
	t_token *aux;
	int	i;
	int	flag;

	aux = *list;
	while (aux)
	{
		i = 0;
		flag = 0;
		while (aux->data[i])
		{
			//TODO
			//ISSUE!! if there's more than one expands in the word must expand
			// preciso dormir .....
			if (aux->data[i] == '$' && aux->data[i + 1])
			{
				flag = 1;
				i++;
				while (aux->data[i++] == '$')
					flag++;
				if (flag <= 2)
				{
					//set no error
					aux->error_code = 0;
					//set token type in it's structure
					aux->type = EXPAND;
					printf("token %i is expand\n", aux->index);
				}
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}
