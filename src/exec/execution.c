/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/07 03:19:58 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_which_builtin(t_shell *shell, t_token *current)
{
	if (current->cmd[0] == NULL)
		return (0);
	if (ft_strcmp(current->cmd[0], "echo") == 0)
		return (ft_builtin_echo(current));
	else if (ft_strcmp(current->cmd[0], "cd") == 0)
		return (ft_builtin_cd(current));
	else if (ft_strcmp(current->cmd[0], "pwd") == 0)
		return (ft_builtin_pwd());
	else if (ft_strcmp(current->cmd[0], "export") == 0)
		return (ft_builtin_export(shell));
	else if (ft_strcmp(current->cmd[0], "unset") == 0)
		return (ft_builtin_unset(current));
	else if (ft_strcmp(current->cmd[0], "env") == 0)
		return (ft_builtin_env(shell));
	else if (ft_strcmp(current->cmd[0], "exit") == 0)
		return (ft_builtin_exit(shell));
	else
		return (1);
}

int	ft_execution(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	if (!aux)
		return (0);
	while (aux && aux->cmd[0])
	{
		if (!(ft_which_builtin(shell, aux)))
			return (0);
		else
		{
			ft_check_cmd(aux);
			ft_free_env_strs(shell);
			break ;
		}
		aux = aux->next;
	}
	return (0);
}
