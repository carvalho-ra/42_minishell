/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:15 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/21 15:52:58 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// function that checks if the command is valid
// returns 0 if it is, -1 if it isn't
int	ft_check_cmd(t_token *current)
{
	char	*cmd;
	char	**args;

	cmd = NULL;
	if (ft_is_executable(current->cmd[0]) == -1)
		return (1);
	else if ((current->cmd[0][0] == '.' && current->cmd[0][1] == '/')
			|| current->cmd[0][0] == '/' || (current->cmd[0][0] == '.'
			&& current->cmd[0][1] == '.' && current->cmd[0][2] == '/'))
		cmd = ft_strdup(current->cmd[0]);
	ft_env_to_str(current->shell);
	if (!cmd)
		cmd = ft_search_cmd(ft_add_cmd(current, ft_get_all_paths(current)));
	args = current->cmd;
	if (!cmd)
	{
		ft_print_error_msg(args[0], "comando não encontrado", 127);
		ft_free_ptrs(&cmd, NULL);
		return (-1);
	}
	else
		ft_execve(current, cmd);
	return (0);
}

// function that executes the command
// returns 0 if it is executable, -1 on execve error
int	ft_execve(t_token *current, char *cmd)
{
	pid_t	pid;

	if (ft_count_pipes(current->shell) > 0)
		ft_execve_core(current, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
		{
			ft_signal_reset();
			ft_execve_core(current, cmd);
		}
		else
		{
			waitpid(pid, &g_error_code, 0);
			if (WIFEXITED(g_error_code))
				g_error_code = WEXITSTATUS(g_error_code);
			if (WIFSIGNALED(g_error_code))
				g_error_code = 128 + WTERMSIG(g_error_code);
			ft_free_ptrs(&cmd, NULL);
		}
	}
	return (0);
}

// function that executes the command
int	ft_execve_core(t_token *current, char *cmd)
{
	if (execve(cmd, current->cmd, current->shell->env_strs) == -1)
	{
		ft_print_error_msg(cmd, "Arquivo ou diretório inexistente", 127);
		exit(g_error_code);
	}
	return (0);
}
