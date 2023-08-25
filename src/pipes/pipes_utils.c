/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:25 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/24 11:58:13 by rcarvalh         ###   ########.fr       */
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

	aux = ft_begin_sentence(current);
	i = 0;
	while (aux && aux->type != PIPE)
	{
		if (aux->type >= REDIRECT_IN && aux->type <= HEREDOC)
			i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_count_cmds(t_token *token)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = ft_begin_sentence(token);
	while (aux && aux->type != PIPE)
	{
		if (aux->type == CMD)
			i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_count_all_cmds(t_shell *shell)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = shell->list;
	while (aux)
	{
		if (aux->type == CMD)
			i++;
		aux = aux->next;
	}
	return (i);
}
