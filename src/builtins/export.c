/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:39:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/07 11:16:29 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Adds or replaces environment variables in the list.
int	ft_builtin_export(t_token *current)
{
	t_token	*aux;
	t_env	*env_list;
	int		env_index;

	aux = current->next;
	if (!aux)
		return (0);
	env_list = current->shell->env;
	if (ft_is_valid_key(aux->str))
	{
		ft_add_to_env_list(env_list, aux->str, 6);
		env_index = ft_is_key_duplicate(env_list, aux->str, 6);
		if (env_index > -1)
			ft_replace_env(env_list, env_index, aux->str);
		else
		{
			while (env_list->next)
				env_list = env_list->next;
			env_list->next = ft_create_env_node(ft_strdup(aux->str));
		}
	}
	else
		return (0);
	return (0);
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
	if (name[0] == '=')
	{
		ft_putstr_fd("minishell: export: `=': \
não é um identificador válido\n", 2);
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
			i++;
		if ((origin == 6 && env->str[i] == '=' && key[i] == '=')
			|| (origin != 6 && env->str[i] == '='
				&& (key[i] == '\0' || key[i] == '=')))
			return (j);
		i = 0;
		j++;
		env = env->next;
	}
	return (-1);
}

// Returns the index of the node that's been created or replaced.
int	ft_add_to_env_list(t_env *env_list, char *new_env, int origin)
{
	int		env_index;

	env_index = ft_is_key_duplicate(env_list, new_env, origin);
	if (env_index > -1)
		ft_replace_env(env_list, env_index, new_env);
	else
	{
		env_index = 0;
		while (env_list->next)
		{
			env_index++;
			env_list = env_list->next;
		}
		env_list->next = ft_create_env_node(ft_strdup(new_env));
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
	free(env->str);
	env->str = ft_strdup(new_value);
	return (TRUE);
}
