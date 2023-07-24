#include "../../inc/minishell.h"

//TODO Se nome for aceitável, mas não tiver =, não adiciona.
//TODO Se nome for aceitável e tiver =, mas nada depois, adiciona valor vazio

// 
int	ft_builtin_export(t_shell *shell)
{
	t_token	*aux;
	t_env	*env;

	aux = shell->list->next;
	env = shell->env;
	printf("variável de ambiente a implementar: %s\n", aux->str);
	if (ft_is_valid_env_name(aux->str))
	{
	//TODO comparar cada item da lista de variáveis de ambiente
	//TODO se já existir, sobrescrever (free na antiga e atribuir nova)
	//TODO se não existir, criar
		
		while (env->next)
		{
			env = env->next;// anda até o final da lista de nodos env
		}
		env->next = ft_create_env_node(ft_strdup(aux->str)); // adiciona nodo à lista de t_env
		//aqui não dava pra usar ft_add_env, pq ela limpa memória do char * passado pra ela. 
	}
	else
	{
		ft_putstr_fd("minishell: export: nome inválido\n", 2);
		return (1); // retorno em caso de erro
	}
	return (1); //retorno original deveria ser 0, mas a função que chama
	// pergunta se é builtin, então o esperado seria TRUE. Trocar no futuro.
}

int	ft_is_valid_env_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (0);
	while (name[i] != '=' || name[i] != '\0')
	{
		while (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		return (1);
	}
	return (0);
}

// The export builtin adds the variable name to the environment with the value
// value, if name doesn't already exist. If name does exist in the environment,
// then its value is changed to value if overwrite is nonzero; if overwrite is
// zero, then the value of name is not changed. This builtin returns true unless
// an invalid option is given or name is read-only.
//
// If the name argument contains a ‘=’, then the export builtin assigns a value
// to the environment variable name. Otherwise, the environment variable name is
// removed from the environment of the executed command.
//
// The return status is zero unless an invalid option is encountered, an attempt
// is made to define a function using ‘-f foo=bar’, an attempt is made to export
// a function using the ‘-f’ option with a name that is not a valid function
// name, an attempt is made to export an array variable using the ‘-a’ option,
// one of the names is not a valid shell variable name, an attempt is made to
// export a variable that is not an integer, etc.
//
// To mimic the export bash command, we need to check if the variable name is
// valid. A valid variable name is any string of alphanumeric characters, plus
// the underscore, not starting with a number. We also need to check if the
// variable name is already in the environment. If it is, we need to change its
// value. If it isn't, we need to add it to the environment.
//