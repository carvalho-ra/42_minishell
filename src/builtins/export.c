/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:39:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/31 17:18:21 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Adds or replaces environment variables in the list.
int	ft_builtin_export(t_shell *shell)
{
	t_token	*aux;
	t_env	*env_list;

	aux = shell->list->next;
	env_list = shell->env;
	printf("\t\tvariável de ambiente a implementar: %s\n", aux->str);
	if (ft_is_valid_key(aux->str))
	{
		ft_add_to_env_list(env_list, aux->str, BUILTIN_EXPORT); //* EM TESE É ISSO
	// compara cada item da lista de variáveis de ambiente e pega o índice, caso ache
	/*	env_index = ft_is_key_duplicate(env_list, aux->str, BUILTIN_EXPORT);
		printf("\t\tIndex %i\n", env_index);
		if (env_index > -1)
			ft_replace_env(env_list, env_index, aux->str);
			// se já existe, sobrescreve
		else
		{
			while (env_list->next)
				env_list = env_list->next;
				// anda até o final da lista de nós env_list
			env_list->next = ft_create_env_node(ft_strdup(aux->str));
			// adiciona nó à lista t_env
			//aqui não dava pra usar ft_add_env, pq ela limpa memória do char * passado pra ela. 
		}*/
	}
	else
		return (2);
		// retorno em caso de erro
	return (1);
	//! retorno original caso sucesso deveria ser 0, mas a função que chama
	//! pergunta se é builtin, então o esperado seria TRUE. Precisamos mudar.
}

// If the key is not valid, prints a message and returns FALSE.
// If it is valid, but doesn't have an equal sign, returns FALSE, but doesn't
// print any error message. This way it is not added to the environment list.
// If it has an equal sign, even with nothing after it, returns TRUE.
int	ft_is_valid_key(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
	{
		ft_putstr_fd("minishell: export: nome inválido\n", 2);
		return (FALSE);
	}
	while (name[i] != '=' && name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: export: nome inválido\n", 2);
			return (FALSE);
		}
		i++;
	}
	if (name[i] == '=')
		return (TRUE);
	return (FALSE);
}
// A key is not valid if it starts with a number, or if it contains any
// character that is not alphanumeric or an underscore.

// Goes through the entire list of environment variables, comparing the name of
// each node with the name passed as argument (both up to the equal sign).
//*Returns the index of the node if it finds a match, or -1 if it's unique.
//*If the origin is export, it compares only the keys.
int	ft_is_key_duplicate(t_env *env, char *key, int origin)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env)
	{
		while (env->str[i] == key[i] && env->str[i] != '=' && key[i] != '=')
		{
			printf("\t\tComparando %c com %c\n", env->str[i], key[i]);
			i++;
		}
		if ((origin == BUILTIN_EXPORT && env->str[i] == '=' && key[i] == '=')
			|| (origin != BUILTIN_EXPORT && env->str[i] == '='
				&& (key[i] == '\0' || key[i] == '=')))
		{
			printf("\t\tAchou duplicada!\n\t\tDuplicada: %s\n", env->str);
			return (j);
		}
		i = 0;
		j++;
		env = env->next;
	}
	printf("\t\tNão achou duplicada…\n");
	return (-1);
}

// Retrieves only the key of the environment variable, up to the equal sign.
/*char	*ft_get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}*/

// Returns the index of the node that's been created or replaced.
int	ft_add_to_env_list(t_env *env_list, char *new_env, int origin)
{
	int		env_index;

	env_index = ft_is_key_duplicate(env_list, new_env, origin);
	printf("\t\tIndex %i\n", env_index);
	if (env_index > -1)
		ft_replace_env(env_list, env_index, new_env);
		// se já existe, sobrescreve
	else
	{
		env_index = 0;
		while (env_list->next)
		{
			env_index++;
			env_list = env_list->next;
			// anda até o final da lista de nós env_list
		}
		env_list->next = ft_create_env_node(ft_strdup(new_env));
		// adiciona nó à lista t_env
		//aqui não dava pra usar ft_add_env, pq ela limpa memória do char * passado pra ela.
	}
	return (env_index);
}

// Goes through the entire list of environment variables, comparing the name of
// each node with the name passed as argument (both up to the equal sign).
// If it finds a match, it changes the value of the node to the value passed as
// argument.
int	ft_replace_env(t_env *env, int index, char *new_value)
{
	while (index > 0)
	{
		index--;
		env = env->next;
	}
	printf("\t\tChegou no nó certo (%s - %s)\n", env->str, new_value); //!apagar
	free(env->str);
	env->str = ft_strdup(new_value);
	return (TRUE);
}
