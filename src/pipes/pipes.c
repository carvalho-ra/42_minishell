/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:39:06 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/21 22:42:03 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_load_pipes(t_token *list)
{
	t_token	*aux;

	aux = list;
	while (aux)
	{
		if (aux->type == PIPE)
		{
			pipe(aux->pipe);
			printf("token %i\n", aux->index);
			printf("type %i\n", aux->type);
			printf("pipe[0] = %i\n", aux->pipe[0]);
			printf("pipe[1] = %i\n", aux->pipe[1]);
		}
		aux = aux->next;
	}
	return (0);
}

// Set the fds to token values during execution
void	ft_set_pipe_fds(t_token *token_cmd, t_token *token_pipe)
{
	printf("set pipe token %i\n", token_cmd->index);
	printf("type %i\n", token_cmd->type);
	printf("pipe[0] = %i\n", token_cmd->pipe[0]);
	if (token_pipe->pipe[0] != -1)
	{
		printf("set_in\n");
		token_cmd->shell->pipe[0] = dup(STDOUT_FILENO);
		dup2(token_pipe->pipe[0], STDOUT_FILENO);
		close(token_pipe->pipe[0]);
	}
	if (token_pipe->pipe[1] != -1)
	{
		printf("set_out\n");
		token_cmd->shell->pipe[1] = dup(STDOUT_FILENO);
		dup2(token_pipe->pipe[1], STDOUT_FILENO);
		close(token_pipe->pipe[1]);
	}
}

// Restores the fds to backup values of struct shell
void	ft_reset_pipe_fds(t_token *token_cmd)
{
	printf("reset pipe token %i\n", token_cmd->index);
	if (token_cmd->pipe[0] != -1)
	{
		printf("reset_in\n");
		dup2(token_cmd->shell->pipe[0], STDIN_FILENO);
		close(token_cmd->shell->pipe[0]);
	}
	if (token_cmd->pipe[1] != -1)
	{
		printf("reset_out\n");
		dup2(token_cmd->shell->pipe[1], STDOUT_FILENO);
		close(token_cmd->shell->pipe[1]);
	}
}
