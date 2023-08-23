/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:25 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/23 15:08:58 by rcarvalh         ###   ########.fr       */
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

int	ft_any_more_pipes(t_token *current)
{
	int		i;

	i = 0;
	while (current)
	{
		if (current->type == PIPE)
			i++;
		current = current->next;
	}
	return (i);
}

int	ft_valid_sentence(t_token *current)
{
	int		i;

	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD)
			i++;
		current = current->next;
	}
	if (i == 0 && (!current || current->type == PIPE))
		return (0);
	return (i);
}

t_token	*ft_begin_sentence(t_token *token)
{
	t_token	*aux;
	t_token	*ref;

	aux = token->shell->list;
	ref = token->shell->list;
	while (aux && aux != token)
	{
		if (aux->type == PIPE)
		{
			ref = aux->next;
		}
		aux = aux->next;
	}
	return (ref);
}
