/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:25 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/23 15:50:44 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_pipes(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == PIPE)
			i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_count_redirs(t_token *current)
{
	t_token	*aux;
	int		i;

	aux = current;
	i = 0;
	while (aux && aux->type != PIPE)
	{
		if (aux->type >= REDIRECT_IN && aux->type <= HEREDOC)
			i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_count_cmds(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == CMD)
			i++;
		aux = aux->next;
	}
	return (i);
}
