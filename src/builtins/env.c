/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:48 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/31 19:46:24 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//?Runs a program in a modified environment. Sets each name to value in the
//?environment and runs the given command.
// Displays the environment variables.

//TODO
/*
[ ] devia receber um t_token *current e a partir dele chegar na lista?
*/

int	ft_builtin_env(t_shell *shell)
{
	t_env	*env;

	printf("NA BUILTIN ENV\n");
	env = shell->env;
	while (env)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
	return (1);
}
