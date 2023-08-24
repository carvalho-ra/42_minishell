/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:39:06 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/24 10:51:46 by rcarvalh         ###   ########.fr       */
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
			pipe(aux->pipe);
		aux = aux->next;
	}
	return (0);
}

// Set the fds to token values during execution
void	ft_set_pipe_fds(t_token *current)
{
	while (current && current->type != PIPE)
		current = current->next;
	if (current)
	{
		close (current->pipe[0]);
		dup2(current->pipe[1], STDOUT_FILENO);
		close(current->pipe[1]);
	}
}

// Restores the fds to backup values of struct shell
void	ft_reset_pipe_fds(t_token *current)
{
	t_token	*aux;

	aux = current;
	while (current && current->type != PIPE)
		current = current->next;
	if (current)
	{
		close(current->pipe[1]);
		dup2(current->pipe[0], STDIN_FILENO);
		close(current->pipe[0]);
	}
	else
	{
		dup2(aux->shell->fd_in, STDIN_FILENO);
		dup2(aux->shell->fd_out, STDOUT_FILENO);
	}
}
