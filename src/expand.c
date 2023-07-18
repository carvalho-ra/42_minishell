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
		while (aux->str[i])
		{
			i = (ft_single_quote(aux->str, i));
			if (aux->str[i] == '$' && aux->str[i + 1] != '$'
				&& aux->str[i - 1] != '$')
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
	char	*prep_exp;

	aux = shell->list;
	while (aux)
	{
		if (aux->type == EXPAND)
		{
			printf("expandir [%s]\n", aux->str);
			prep_exp = ft_prep_expand(aux->str);
			ft_is_expand(prep_exp, shell);
		}
		aux = aux->next;
	}
}

// apagar aspas duplas
// apagar aspas simples e nao faz mais nada
// cortar a variavel que vai expandir
// é só a varivel??

char *ft_prep_expand(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	if (tmp[i] == 34)
		tmp = ft_strtrim(tmp, "\"");
	else
		tmp = ft_strdup(tmp);
	return (tmp);
}

int ft_is_expand(char *str, t_shell *shell)
{
	char	*prev;
	char	*var;
	char	*final;
	int		i;
	int 	start;

	i = 0;
	start = 0;
	var = NULL;
	prev = NULL;
	final = NULL;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (start != i)
			prev = ft_substr(str, start, i - start);
		if (str[i] == '$' && str[i + 1])
			i++;
		start = i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (start != i)
			var = ft_substr(str, start, i - start);
		start = i;
		//write(2, "here", 4);
		var = ft_look_for_in_env(var, shell);
		if (prev && var && !final)
			final = ft_strjoin(prev, var);
		else if (!prev && var && final)
			final = ft_strjoin(final, var);
		else if (!prev && var && !final)
			final = var;
		else if (prev && var && final)
		{
			final = ft_strjoin(final, prev);
			final = ft_strjoin(final, var);
		}
		else if (prev && !var && final)
			final = ft_strjoin(final, prev);
		else if (prev && !var && !final)
			final = prev;
		else if (!prev && !var && !final)
			break ;
		printf("prev variable [%s]\n", prev);
		printf("look for in env [%s]\n", var);
		printf("expanded [%s]\n", final);
		prev = NULL;
		var = NULL;
		//join prev + str expanded + prev 
		//i++;
	}
	//free(str, prev, str);
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
		if (!ft_strncmp(str, aux->str, ft_strlen(str))
			&& aux->str[ft_strlen(str)] == '=')
		{
			ret = ft_substr(aux->str, (ft_strlen(str) + 1),
				ft_strlen(aux->str) - (ft_strlen(str) + 1));
		}
		aux = aux->next;
	}
	return (ret);
}

//procurar com ft_strcmp(env);

//colocar em um loop para pagar string previa concatenar com a parte do ENV, e continuar

// strdup do strlen + 1 pra pular o igual da variavel;

//retorna string expandida
