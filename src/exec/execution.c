/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/19 16:19:36 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Checks if a given command is built-in.
// Returns 0 if it's built-in, 1 if it's not.
int	ft_which_builtin(t_token *current)
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
		return (ft_builtin_export(current));
	else if (ft_strcmp(current->cmd[0], "unset") == 0)
		return (ft_builtin_unset(current));
	else if (ft_strcmp(current->cmd[0], "env") == 0)
		return (ft_builtin_env(current));
	else if (ft_strcmp(current->cmd[0], "exit") == 0)
		return (ft_builtin_exit(current));
	else
		return (1);
}

//function that sends command to execution if it's not a builtin
//returns 0 if it works, 1 if it doesn't
int	ft_execution(t_shell *shell)
{
	t_token	*token;

	token = shell->list;
	if (!token)
		return (0);
	if (ft_redirector(token) >= 0)
	{
		while (token)
		{
			ft_set_fds(token);
			if (token->type == CMD)
			{
				if ((ft_which_builtin(token)))
				{
					ft_check_cmd(token);
					ft_free_env_strs(shell);
				}
				ft_reset_fds(token);
			}
			else if (token->type >= REDIRECT_IN && token->type <= APPEND
				&& token->type == ERR)
				ft_reset_fds(token);
			token = token->next;
		}
	}
	return (0);
}
