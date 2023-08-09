/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:39:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/08 21:28:16 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Adds or replaces environment variables in the list.
int	ft_builtin_export(t_token *current)
{
	int		env_index;

	if (!current->cmd[1])
	{
		g_error_code = 0;
		return (0);
	}
	if (ft_is_valid_key(current->cmd[1], current))
	{
		ft_add_to_env_list(current->shell->env, current->cmd[1], 6);
		env_index = ft_is_key_duplicate(current->shell->env,
				current->cmd[1], 6);
		if (env_index > -1)
			ft_replace_env(current->shell->env, env_index, current->cmd[1]);
		else
		{
			while (current->shell->env->next)
				current->shell->env = current->shell->env->next;
			current->shell->env->next = ft_create_env_node
				(ft_strdup(current->cmd[1]));
		}
	}
	else
		return (0);
	return (0);
}
