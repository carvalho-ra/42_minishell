#include "../inc/minishell.h"

//TODO need to export more than 1 variable at the same time? in the same line

// ler regras do export (man) 

// ler regras variaveis shell

//unset em variavel inexistente é igual ao comportamento normal, não dá erro

int ft_copy_env(t_shell *shell, char **envp)
{
	int		i;

	shell->new_env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_add_env(shell, ft_strdup((const char *)envp[i]), 1);
		i++;
	}
	return (0);
}

// pseudocode

// look for expand ($)
// - function to iterate through strings
// of each node looking for $ (ISSUE! consider $$???)

int ft_confirm_expand(t_shell *shell)
{
	t_token *aux;
	int	i;

	aux = shell->list;
	while (aux)
	{
		i = 0;
		while (aux->data[i])
		{
			i = (ft_single_quote(aux->data, i));
			if (aux->data[i] == '$' && aux->data[i + 1] != '$'
				&& aux->data[i - 1] != '$')
			{
				aux->error_code = 0;
				aux->type = EXPAND;
				printf("token %i is expand\n", aux->index);
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}

void ft_vars_to_expand(t_shell *shell)
{
	t_token *aux;

	aux = shell->list;
	while (aux)
	{
		if (aux->type == EXPAND)
		{
			printf("expandir [%s]\n", aux->data);
			ft_is_expand(ft_prep_expand(aux->data), shell);
		}
		aux = aux->next;
	}
}

// apagar aspas duplas
// apagar aspas simples e nao faz mais nada
// cortar a variavel que vai expandir
// é só a varivel??

char *ft_prep_expand(char *data)
{
	int		i;
	char	*str;
	//char	**ret;

	i = 0;
	str = NULL;
	if (data[i] == 34)
		str = ft_strtrim(data, "\"");
	else
		str = ft_strdup(data);
	return (str);
}

int	ft_is_expand(char *data, t_shell *shell)
{
	char	*final;
	int		i;
	int 	start;

	i = 0;
	start = 0;
	final = NULL;
	while (data[i])
	{
		start = i;
		if (data[i] && data[i] != '$')
		{
			while (data[i] && data[i] != '$')
				i++;
			if (start != i && !final)
				final = ft_substr(data, start, i - start);
			else
				final = ft_strjoin(final, ft_substr(data, start, i - start));
		}
		if (data[i] && data[i] == '$')
		{
			i++;
			start = i;
			while (data[i] && (ft_isalnum(data[i]) || data[i] == '_'))
				i++;
			if (start != i && !final && ft_look_for_in_env(ft_substr(data, start, i - start), shell))
				final = ft_look_for_in_env(ft_substr(data, start, i - start), shell);
			else if (start != i && final && ft_look_for_in_env(ft_substr(data, start, i - start), shell))
				final = ft_strjoin(final, ft_look_for_in_env(ft_substr(data, start, i - start), shell));
		}
		printf("expanded [%s]\n", final);

	}
	return (0);
}

char	*ft_look_for_in_env(char *str, t_shell *shell)
{
	t_token *aux;
	char	*ret;

	aux = shell->new_env;
	ret = NULL;
	while (aux->next)
	{
		if (!ft_strncmp(str, aux->data, ft_strlen(str))
			&& aux->data[ft_strlen(str)] == '=')
		{
			ret = ft_substr(aux->data, (ft_strlen(str) + 1),
				ft_strlen(aux->data) - (ft_strlen(str) + 1));
		}
		aux = aux->next;
	}
	return (ret);
}

//procurar com ft_strcmp(env);

//colocar em um loop para pagar string previa concatenar com a parte do ENV, e continuar

// strdup do strlen + 1 pra pular o igual da variavel;

//retorna string expandida
