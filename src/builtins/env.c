/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:38:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/26 05:36:20 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//?Runs a program in a modified environment. Sets each name to value in the
//?environment and runs the given command.
// Displays the environment variables.
int	ft_builtin_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
	return (1);
}
