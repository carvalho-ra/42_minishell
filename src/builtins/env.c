/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:38:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/22 12:42:02 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//?Runs a program in a modified environment. Sets each name to value in the
//?environment and runs the given command.
// Displays the environment variables.
int	ft_builtin_env(t_shell *shell)
{
	t_token	*aux;

	aux = shell->new_env;
	while (aux)
	{
		printf("%s\n", aux->data);
		aux = aux->next;
	}
	return (1);
}
