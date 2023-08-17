/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:41:18 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/17 13:41:59 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Set the fds to token values during execution
//if the token fd is different from the default
//backup fds in struct shell
//set the fds to the token fds
void	ft_set_fds(struct s_token *token)
{
	if (token->pipe[0] > 2)
	{
		token->shell->backup[0] = dup(STDIN_FILENO);
		dup2(token->pipe[0], STDIN_FILENO);
		close(token->pipe[0]);
	}
	if (token->pipe[1] > 2)
	{
		token->shell->backup[1] = dup(STDOUT_FILENO);
		dup2(token->pipe[1], STDOUT_FILENO);
		close(token->pipe[1]);
	}
}

// Restores the fds to backup values of struct shell
void	ft_reset_fds(struct s_token *token)
{
	if (token->shell->backup[0] > 2)
	{
		dup2(token->shell->backup[0], STDIN_FILENO);
		close(token->shell->backup[0]);
	}
	if (token->shell->backup[1] > 2)
	{
		dup2(token->shell->backup[1], STDOUT_FILENO);
		close(token->shell->backup[1]);
	}
}
