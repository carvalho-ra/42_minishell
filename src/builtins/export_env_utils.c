/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:19:48 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 21:19:51 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
