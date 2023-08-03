/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:48 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/03 14:09:18 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	return (0);
}
