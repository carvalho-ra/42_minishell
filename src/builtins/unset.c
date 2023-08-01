/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:33:10 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/01 05:39:44 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Deletes environment variables from the list.
int	ft_builtin_unset(t_shell *shell)
{
	t_token	*aux;
	t_env	*env;
	int		env_index;

	aux = shell->list->next;
	env = shell->env;
	env_index = ft_is_key_duplicate(env, aux->str, 1);
	printf("\t\tIndex %i\n", env_index);
	if (env_index > -1)
		ft_delete_env(env, env_index);
	else
		return (2);
	return (0);
}

// Recreates the function above, but with char* shell->env_strs[0] instead of a list.
int	ft_builtin_unset_matrix(t_shell *shell)
{
	int	index;

	index = ft_is_key_duplicate_matrix(shell->env_strs, shell->list->next->str, 1);
	if (index > -1)
		ft_delete_env_from_matrix(shell, index);
	else
		return (2);
	return (0);
}

// Iterates through the environment list until it reaches the passed int,
// then deletes the node, freeing its memory and replacing the previous node's
// next pointer to the next node.
int	ft_delete_env(t_env *env, int index)
{
	t_env	*current;
	t_env	*previous;
	int		i;

	i = 0;
	current = env;
	previous = env;
	// Se for o primeiro nó, apenas move o ponteiro para o próximo e libera.
	if (index == 0)
	{
		env = env->next;
		free(current->str);
		free(current);
		return (0);
	}
	// Se não for o primeiro nó, avança pela lista até chegar no correto,
	// libera a memória e substitui o ponteiro next do nó anterior para o
	// próximo nó.
	while (i < index)
	{
		previous = current;
		current = current->next;
		i++;
	}
	if (current->next == NULL)
		previous->next = NULL;
	else if (current->next != NULL)
		previous->next = current->next;
	free(current->str);
	free(current);
	return (0);
}

// Recreates the function above, but with char* shell->env_strs[0] instead of a list.
int	ft_delete_env_from_matrix(t_shell *shell, int index)
{
	int	i;

	i = index;
	while (shell->env_strs[i + 1] != NULL)
	{
		shell->env_strs[i] = shell->env_strs[i + 1];
		i++;
	}
	shell->env_strs[i] = NULL;
	return (0);
}
