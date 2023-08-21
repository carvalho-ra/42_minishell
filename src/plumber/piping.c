/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:38:12 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/18 19:44:28 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//! Builtins precisam rodar no processo filho caso iniciem ou encerrem a pipeline.

int	ft_has_pipes(struct s_shell *shell)
{
	t_token	*token;
	t_token	*next_valid;

	if (shell->pipes > 0) // Se soubermos que há pelo menos um pipe
	{
		token = shell->list; // Pegamos a lista de tokens
		while (token && (token->type != CMD
				|| ((token->type >= REDIRECT_IN && token->type <= HEREDOC))))
			token = token->next;
		next_valid = ft_next_valid(token);
		if (!next_valid)
			next_valid = token;
		if (next_valid != token)
			token->not_the_last = 1;
		if (token->not_the_last == 1)
			ft_load_pipes(token, next_valid);
		else if (token->not_the_last == 0)
			ft_load_pipes(token, NULL);
	}
	shell->pipes--;
	return (shell->pipes);
}

void	ft_load_pipes(t_token *token, t_token *next_valid)
{
	if (!token)
		return ;
	/*if (!next_valid)
	{
		next_valid = token;
		ft_close_pipes(token); // Se não houver próximo válido, fecha os pipes
	}*/
	if (token->shell->pipes > 0) // Se tiver um pipe, 
	{
		close(token->pipe[0]);
		pipe(token->pipe);
		//printf("\t\tquantidade de pipes: %i\n", token->shell->pipes);
		//token->shell->pipes--;
	}
	if (token->pipe[0] != -1)
	{
		dup2(token->pipe[0], STDIN_FILENO);
	}
	if (pipe(token->pipe) < 0)
	{
		ft_putstr_fd("minishell: erro ao criar pipe\n", 2);
		g_error_code = 1;
	}
}

void	ft_close_pipes(t_token *token)
{
	if (token->pipe[0] != -1)
		close(token->pipe[0]);
	if (token->shell->pipes > 0)
		close(token->pipe[1]);
}

void	ft_copy_fds(int *origin, int *destination)
{
	destination[0] = origin[0];
	destination[1] = origin[1];
}

int	ft_set_pipe(t_token *token)
{
	int	output;

	output = 0;
	if (token->not_the_last == 0)
		return (output);
	output = pipe(token->pipe);
	if (output == -1)
	{
		// erro de pipe
		return (-1);
	}
	return (0);
}
