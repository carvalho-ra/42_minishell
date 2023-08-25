/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/24 15:03:42 by rcarvalh         ###   ########.fr       */
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

//funtion that validates sentence with no command
int	ft_sentence_no_cmd(t_token *current)
{
	if ((current->type >= REDIRECT_IN && current->type <= HEREDOC)
		&& !ft_count_cmds(current))
	{
		if (ft_redirector(current) < 0)
		{
			ft_reset_pipe_fds(current);
			return (0);
		}
		ft_reset_pipe_fds(current);
	}
	return (0);
}

//function that organizes execution
int	ft_master_exec(t_shell *shell)
{
	t_token	*current;

	current = shell->list;
	if (!ft_count_pipes(shell))
		ft_execution(current);
	else
	{
		while (current)
		{
			ft_load_pipes(shell->list);
			ft_sentence_no_cmd(current);
			if (current->type == CMD)
				ft_forked_exec(current);
			if (current)
				current = current->next;
		}
		ft_wait_childs(shell->list);
	}
	return (0);
}

//function that performs foked executions
t_token	*ft_forked_exec(t_token *current)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		ft_set_pipe_fds(current);
		ft_signal_reset();
		current = ft_execution(current);
	}
	else
		ft_reset_pipe_fds(current);
	return (current);
}

//function that execute the commands
t_token	*ft_execution(t_token *current)
{
	if (ft_redirector(current) < 0)
		return (0);
	while (current)
	{
		ft_set_fds(current);
		if (current->type == CMD)
		{
			if ((ft_which_builtin(current)))
			{
				ft_check_cmd(current);
				ft_free_env_strs(current->shell);
			}
			else if (ft_count_pipes(current->shell) > 0)
			{
				ft_reset_fds(current);
				exit (g_error_code);
			}
			ft_reset_fds(current);
		}
		else
			ft_reset_fds(current);
		current = current->next;
	}
	return (0);
}
