/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/31 13:06:09 by rcarvalh         ###   ########.fr       */
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
			return (ft_builtin_echo(shell));
		else if (ft_strcmp(aux->str, "cd") == 0)
		{
			printf("token %i is builtin cd\n", aux->index);
			return (ft_builtin_cd(shell));
		}
		else if (ft_strcmp(aux->str, "pwd") == 0)
		{
			printf("token %i is builtin pwd\n", aux->index);
			return (ft_builtin_pwd());
		}
		else if (ft_strcmp(aux->str, "export") == 0)
		{
			printf("token %i is builtin export\n", aux->index);
			return (ft_builtin_export(shell));
		}
		else if (ft_strcmp(aux->str, "unset") == 0)
		{
			printf("token %i is builtin unset\n", aux->index);
			//return (ft_builtin_unset(shell));
		}
		else if (ft_strcmp(aux->str, "env") == 0) // Tem aqui e na main?
			return (ft_builtin_env(shell));
		else if (ft_strcmp(aux->str, "exit") == 0) // Tem aqui e na main?
		{
			printf("token %i is builtin exit\n", aux->index);
			return (ft_builtin_exit(shell));
		}
		else
		{
			//printf("chama execve\n");
			ft_execve(aux);
			ft_free_env_strs(shell);	
			break ;
		}
		aux = aux->next;
	}
	
	return (0);
}
