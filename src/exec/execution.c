/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/15 09:59:03 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Goes through the token list looking for redirectors or pipes.
// If it finds any, calls the respective function to load the input/output.
// Returns the sum of the redirectors found.
// This must be done before the execution of the command.
int	ft_which_redirector(struct s_token *token)
{
	int	ret;

	ret = 0;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			ft_load_heredoc(token->next->str);
			//ft_load_input(token);
			ret += HEREDOC;
		}
		if (token->type == REDIRECT_IN)
		{
			ft_load_input(token);
			ret += REDIRECT_IN;
		}
		if (token->type == REDIRECT_OUT || token->type == APPEND)
		{
			ft_load_output(token);
			ret += REDIRECT_OUT;
		}
		/*if (token->type == PIPE)
		{
			ft_load_pipe(token);
			ret += PIPE;
		}*/
		token = token->next;
	}
	return (ret);
}

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
	int		redirected;

	token = shell->list;
	if (!token)
		return (0);
	while (token)
	{
		if (token->type == CMD)
		{
			redirected = ft_which_redirector(token);
			if ((ft_which_builtin(token)))
			{
				ft_check_cmd(token);
				ft_free_env_strs(shell);
			}
		}
		if (redirected)
			ft_reset_fds(token);
		token = token->next;
	}
	return (0);
}
