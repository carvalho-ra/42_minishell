/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:39:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/09 01:01:38 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Adds or replaces environment variables in the list.
int	ft_builtin_export(t_token *current)
{
	int		j;

	j = 1;
	if (!current->cmd[1])
	{
		g_error_code = 0;
		return (0);
	}
	while (current->cmd[j])
	{
		if (ft_is_valid_key(current->cmd[j]))
			ft_add_to_env_list(current->shell->env, current->cmd[j], 6);
		j++;
	}
	return (0);
}
