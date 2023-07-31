/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:33:10 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/31 19:58:00 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Deletes environment variables from the list.
// int	ft_builtin_unset(t_shell *shell)
// {
// 	t_token	*aux;
// 	t_env	*env;
// 	int		env_index;

// 	aux = shell->list->next;
// 	env = shell->env;
// 	env_index = ft_is_key_duplicate(env, aux->str, BUILTIN_UNSET);
// 	printf("\t\tIndex %i\n", env_index);
// 	if (env_index > -1)
// 		ft_delete_env(env, env_index);
// 	else
// 		return (2);
// 	return (1);
// 	//! Deveria ser 0 (exit status 0, all operands successfully unset).
// 	//! Aqui também, retorno padrão de sucesso é 0, mas a função
// 	//! que chama pergunta se é builtin, então esperado é 1. Trocar também.
// }

// // Iterates through the environment list until it reaches the passed int,
// // then deletes the node, freeing its memory and replacing the previous node's
// // next pointer to the next node.
// int	ft_delete_env(t_env *env, int index)
// {
// 	t_env	*current;
// 	t_env	*previous;
// 	int		i;

// 	i = 0;
// 	current = env;
// 	previous = env;
// 	// Se for o primeiro nó, apenas move o ponteiro para o próximo e libera.
// 	if (index == 0)
// 	{
// 		env = env->next;
// 		free(current->str);
// 		free(current);
// 		return (SUCCESS);
// 	}
// 	// Se não for o primeiro nó, avança pela lista até chegar no correto,
// 	// libera a memória e substitui o ponteiro next do nó anterior para o
// 	// próximo nó.
// 	while (i < index)
// 	{
// 		previous = current;
// 		current = current->next;
// 		i++;
// 	}
// 	if (current->next == NULL)
// 		previous->next = NULL;
// 	else if (current->next != NULL)
// 		previous->next = current->next;
// 	free(current->str);
// 	free(current);
// 	return (SUCCESS);
// }
