/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/24 14:39:52 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO Aprimorar processamento.

int	ft_is_builtin(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (ft_strcmp(aux->str, "echo") == 0)
		{
			aux->type = BUILTIN_ECHO;
			printf("token %i is builtin echo\n", aux->index);
			return (ft_builtin_echo(shell));
		}
		if (ft_strcmp(aux->str, "cd") == 0)
		{
			aux->type = BUILTIN_CD;
			printf("token %i is builtin cd\n", aux->index);
			return (ft_builtin_cd(shell));
		}
		if (ft_strcmp(aux->str, "pwd") == 0)
		{
			aux->type = BUILTIN_PWD;
			printf("token %i is builtin pwd\n", aux->index);
			return (ft_builtin_pwd());
		}
		if (ft_strcmp(aux->str, "export") == 0)
		{
			aux->type = BUILTIN_EXPORT;
			printf("token %i is builtin export\n", aux->index);
			return (ft_builtin_export(shell));
		}
		if (ft_strcmp(aux->str, "unset") == 0)
		{
			aux->type = BUILTIN_UNSET;
			printf("token %i is builtin unset\n", aux->index);
			//return (ft_builtin_unset(shell));
		}
		if (ft_strcmp(aux->str, "env") == 0) // Tem aqui e na main?
		{
			aux->type = BUILTIN_ENV;
			printf("token %i is builtin env\n", aux->index);
			return (ft_builtin_env(shell));
		}
		if (ft_strcmp(aux->str, "exit") == 0) // Tem aqui e na main?
		{
			aux->type = BUILTIN_EXIT;
			printf("token %i is builtin exit\n", aux->index);
			//return (ft_builtin_exit(shell));
		}
		aux = aux->next;
	}
	return (0);
}
