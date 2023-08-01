/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:39:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/01 08:01:19 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Adds or replaces environment variables in the list.
int	ft_builtin_export(t_shell *shell)
{
	t_token	*aux;
	t_env	*env_list;
	int		env_index;

	aux = shell->list->next;
	env_list = shell->env;
	printf("\t\tvariável de ambiente a implementar: %s\n", aux->str);
	if (ft_is_valid_key(aux->str))
	{
		ft_add_to_env_list(env_list, aux->str, 6); //* EM TESE É ISSO
	// compara cada item da lista de variáveis de ambiente e pega o índice, caso ache
	env_index = ft_is_key_duplicate(env_list, aux->str, 6);
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
		}
	}
	else
		return (2);
		// retorno em caso de erro
	return (1);
	//! retorno original caso sucesso deveria ser 0, mas a função que chama
	//! pergunta se é builtin, então o esperado seria TRUE. Precisamos mudar.
}

// Adds or replaces environment variables in the list.
//* 6 is just a placeholder for the BUILTIN_EXPORT macro, that we got rid of.
//TODO TODAS AS FUNÇÕES CHAMADAS AQUI PRECISAM SER REFEITAS PARA TRABALHAR COM CHAR*
int	ft_builtin_export_matrix(t_shell *shell)
{
	char	*new_env;
	t_env	*env_list;
	int		env_index;
	//size_t	matrix_length;

	new_env = ft_strdup(shell->list->next->str);
	env_list = shell->env;
	//matrix_length = ft_matrix_length(shell->env_strs);
	printf("\t\tvariável de ambiente a implementar: %s\n", new_env);
	if (ft_is_valid_key(new_env))
	{
		ft_add_to_env_list(env_list, new_env, 6);
	// compara cada item da lista de variáveis de ambiente e pega o índice, caso ache
	env_index = ft_is_key_duplicate(env_list, new_env, 6);
		printf("\t\tIndex %i\n", env_index);
		if (env_index > -1)
			ft_replace_env(env_list, env_index, new_env);
			// se já existe, sobrescreve (malloc). Como vou fazer isso com char* sem risco de sobrepor?
		else
		{
			while (shell->env_strs[env_index + 1] != NULL)
				env_index++;
				// anda até o final do array e vai preencher (malloc) o novo índice com new_env
			shell->env_strs[env_index + 1] = ft_strdup(new_env);
			// e adiciona NULL no próximo índice
			shell->env_strs[env_index + 2] = NULL;
			// sinto que vai dar merda
		}
	}
	else
		return (2);
	return (0);
}

size_t	ft_matrix_length(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
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
//*If the origin is export (6), it compares only the keys.
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
		if ((origin == 6 && env->str[i] == '=' && key[i] == '=')
			|| (origin != 6 && env->str[i] == '='
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

// Recreating the function above, but with char* shell->env_strs[0] instead of a list.
int	ft_is_key_duplicate_matrix(char **env_list, char *key, int origin)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_list[j])
	{
		while (env_list[j][i] == key[i] && env_list[j][i] != '=' && key[i] != '=')
		{
			printf("\t\tComparando %c com %c\n", env_list[j][i], key[i]);
			i++;
		}
		if ((origin == 6 && env_list[j][i] == '=' && key[i] == '=')
			|| (origin != 6 && env_list[j][i] == '='
				&& (key[i] == '\0' || key[i] == '=')))
		{
			printf("\t\tAchou duplicada!\n\t\tDuplicada: %s\n", env_list[j]);
			return (j);
		}
		i = 0;
		j++;
	}
	printf("\t\tNão achou duplicada…\n");
	return (-1);
}

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

// Recreating the function above, but with char* shell->env_strs[0] instead of a list.
// Returns the index of the node that's been created or replaced.
int	ft_add_to_env_matrix(char **env_matrix, char *new_env, int origin)
{
	int		env_index;

	env_index = ft_is_key_duplicate_matrix(env_matrix, new_env, origin);
	printf("\t\tIndex %i\n", env_index);
	if (env_index > -1)
		ft_replace_env_matrix(env_matrix, env_index, new_env);
		// se já existe, sobrescreve
	else
	{
		env_index = 0;
		while (env_matrix[env_index])
			env_index++;
			// anda até o final do array e vai preencher (malloc) o novo índice com new_env
		env_matrix[env_index] = ft_strdup(new_env);
		// e adiciona NULL no próximo índice
		env_matrix[env_index + 1] = NULL;
		// sinto que vai dar merda
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

// Recreating the function above, but with char* shell->env_strs[0] instead of a list.
//! Alta periculosidade!
int	ft_replace_env_matrix(char **env_matrix, int index, char *new_value)
{
	free(env_matrix[index]);
	env_matrix[index] = ft_strdup(new_value);
	return (TRUE);
}
