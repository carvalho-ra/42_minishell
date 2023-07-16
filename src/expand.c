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

	aux = *list;
	while (aux)
	{
		i = 0;
		while (aux->data[i])
		{
			i = (ft_single_quote(aux->data, i));
			if (aux->data[i] == '$' && aux->data[i + 1] != '$'
				&& aux->data[i - 1] != '$')
			{
				//set no error
				aux->error_code = 0;
				//set token type in it's structure
				aux->type = EXPAND;
				printf("token %i is expand\n", aux->index);
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}

void ft_vars_to_expand(t_token **list)
{
	t_token *aux;

	aux = *list;
	while (aux)
	{
		if (aux->type == EXPAND)
		{
			printf("expandir [%s]\n", aux->data);
			ft_is_expand(aux->data);
		}
		aux = aux->next;
	}
}

// apagar aspas duplas
// apagar aspas simples e nao faz mais nada
// cortar a variavel que vai expandir
// é só a varivel??

int	ft_is_expand(char *data)
{
	char 	*tmp;
	char	*prev;
	char	*str;
	int		i;
	int 	start;

	i = 0;
	start = 0;
	if (data[i] == 34)
	{
		tmp = ft_strtrim(data, "\"");
		while (tmp[i] && tmp[i] != '$')
			i++;
		prev = ft_substr(tmp, 0, i);
	}
	else
		tmp = ft_strdup(data);
	while (tmp[i] && tmp[i] == '$')
		i++;
	start = i;
	while (tmp[i] && ft_isalpha(tmp[i]))
		i++;
	if (start != i)
	{
		str = ft_substr(tmp, start, i - start);
	}
	printf("look for in env [%s]\n", str);
	return (0);
}

//procurar com ft_strcmp(env);

//colocar em um loop para pagar string previa concatenar com a parte do ENV, e continuar

// strdup do strlen + 1 pra pular o igual da variavel;

//retorna string expandida
