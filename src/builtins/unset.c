/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:33:10 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/03 13:50:30 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Deletes environment variables from the list.
int	ft_builtin_unset(t_token *current)
{
	t_token	*aux;
	t_env	*env;
	int		env_index;

	printf("NA BUILTIN UNSET\n");
	aux = current->next;
	env = current->shell->env;
	if (!current->next || aux->str == NULL)
		return (0);
	env_index = ft_is_key_duplicate(env, aux->str, 1);
	if (env_index > -1)
		ft_delete_env(env, env_index);
	else
		return (0);
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
	if (index == 0)
	{
		env = env->next;
		ft_free_env_node(current);
		return (0);
	}
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
	ft_free_env_node(current);
	return (0);
}

void	ft_free_env_node(t_env *env)
{
	free(env->str);
	env->str = NULL;
	free(env);
	env = NULL;
}
