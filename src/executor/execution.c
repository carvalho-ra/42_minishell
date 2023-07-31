/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/31 20:00:18 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execution(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux && aux->cmd)
	{
		if (ft_strcmp(aux->str, "echo") == 0)
			return (ft_builtin_echo(aux));
		else if (ft_strcmp(aux->str, "cd") == 0)
		{
			//return (ft_builtin_cd(shell));	
		}
		else if (ft_strcmp(aux->str, "pwd") == 0)
			return (ft_builtin_pwd());
		else if (ft_strcmp(aux->str, "export") == 0)
		{
			//return (ft_builtin_export(shell));
		}
		else if (ft_strcmp(aux->str, "unset") == 0)
		{
			//return (ft_builtin_unset(shell));	
		}
		else if (ft_strcmp(aux->str, "env") == 0)
			return (ft_builtin_env(shell));
		else if (ft_strcmp(aux->str, "exit") == 0)
			return (ft_builtin_exit(shell));
		else
		{
			ft_execve(aux);
			ft_free_env_strs(shell);	
			break ;
		}
		aux = aux->next;
	}
	return (0);
}
