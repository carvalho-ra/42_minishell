/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:12 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/16 16:13:28 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Goes through the token list looking for redirectors or pipes.
// If it finds any, calls the respective function to load the input/output.
// Returns the sum of the redirectors found.
// This must be done before the execution of the command.
// TODO Em vez de trocar no token->type REDIRECTOR, trocar no token->type CMD
// TODO Vai precisar percorrer a lista de tokens até achar um pipe ou NULL,
// TODO manter como referência o token-type CMD, dar open nessa referência
// TODO token CMD; token REDIRECT e token FILENAME (pulando os que forem nulo $NO)
//* ft_count_pipes
int	ft_which_redirector(struct s_token *token)
{
	int		ret;
	//int		pipeno;
	t_token	*ref; //Armazena o token que contém o comando

	ret = 0;
	//pipeno = 0;
	ref = token;
	while (ref && ref->type != CMD && ref->type != PIPE) // Referencia o token que tem um comando ou pipe.
		ref = ref->next;
	if (!ref)
		ref = token;
	/*if (token->type == PIPE)
	{
		ret += ft_load_pipe(token) + PIPE;
		pipeno++;
	}*/
	while (token && token->type != PIPE)
	{
		if (token->type == HEREDOC)
			ret += ft_load_heredoc(ft_get_name(token)) + HEREDOC;
		if (token->type == REDIRECT_IN)
			ret += ft_load_input(ref, ft_get_name(token)) + 3;
		if (token->type == REDIRECT_OUT || token->type == APPEND)
			ret += ft_load_output(ref, ft_get_name(token), token->type);
		token = token->next;
	}
	return (ret);
}

char	*ft_get_name(t_token *token)
{
	while (token)
	{
		if (token->type == FILE_NAME || token->type == KEYWORD)
			return (token->str);
		token = token->next;
	}
	return (NULL);
}

/*int	ft_which_redirector(struct s_token *token)
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
		if (token->type == PIPE)
		{
			ft_load_pipe(token);
			ret += PIPE;
		}
		token = token->next;
	}
	return (ret);
}*/

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
	int		status_redir;

	status_redir = 0;
	token = shell->list;
	if (!token)
		return (0);
	status_redir = ft_which_redirector(token);
	while (token)
	{
		//if (token->type == CMD || (token->type >= 2 && token->type <= 6))
		if (status_redir == 2)
			return (-1);
		if (token->type == CMD)
		{
			// redirected = ft_which_redirector(token);
			if ((ft_which_builtin(token)))
			{
				ft_check_cmd(token);
				ft_free_env_strs(shell);
			}
			ft_reset_fds(token);
		}
		ft_reset_fds(token);
		token = token->next;
	}
	return (0);
}
