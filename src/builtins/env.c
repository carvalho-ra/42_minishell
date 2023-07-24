/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:48 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/24 04:36:24 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//?Runs a program in a modified environment. Sets each name to value in the
//?environment and runs the given command.
// Displays the environment variables.
int	ft_builtin_env(t_shell *shell)
{
	t_token	*envs;

	envs = shell->new_env;
	while (envs)
	{
		printf("%s\n", envs->str);
		envs = envs->next;
	}
	return (1);
}
