/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:41:18 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/22 17:24:00 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Set the fds to token values during execution
//if the token fd is different from the default
//backup fds in struct shell
//set the fds to the token fds
void	ft_set_fds(struct s_token *token)
{
	if (token->pipe[IN] > 2)
	{
		printf("\t\tPassou por aqui.\n");
		dup2(token->pipe[IN], STDIN_FILENO);
		close(token->pipe[IN]);
	}
	if (token->pipe[OUT] > 2)
	{
		dup2(token->pipe[OUT], STDOUT_FILENO);
		close(token->pipe[OUT]);
	}
	if (token->fd_in > 2)
	{
		dup2(token->fd_in, STDIN_FILENO);
		close(token->fd_in);
	}
	if (token->fd_out > 2)
	{
		dup2(token->fd_out, STDOUT_FILENO);
		close(token->fd_out);
	}
}

// Restores the fds to backup values of struct shell
void	ft_reset_fds(struct s_token *token)
{
	if (token->pipe[IN] != STDIN_FILENO || token->fd_in != STDIN_FILENO)
	{
		dup2(token->shell->backup[IN], STDIN_FILENO);
		close(token->shell->backup[IN]);
	}
	if (token->pipe[OUT] != STDOUT_FILENO || token->fd_out != STDOUT_FILENO)
	{
		dup2(token->shell->backup[OUT], STDOUT_FILENO);
		close(token->shell->backup[OUT]);
	}
}
