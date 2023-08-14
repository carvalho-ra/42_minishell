/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mark_cmds_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:20:57 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/14 11:27:57 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_mark_cmds(t_shell *shell)
{
	t_token	*aux;
	int		i;
	int		state;

	state = 0;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == PIPE)
			state = 0;
		if (aux->type >= 0 && aux->type <= EXPAND)
		{
			if (aux->str && state == 0)
			{
				aux->type = CMD;
				state = 1;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_mark_args(t_shell *shell)
{
	t_token	*aux;
	int		i;
	int		state;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == CMD)
			state = 0;
		if (!(aux->type >= PIPE && aux->type <= ERR)
			&& !(aux->type >= CMD && aux->type <= KEYWORD) && !(state))
		{
			if (aux->str)
			{
				aux->type = ARG;
			}
		}
		aux = aux->next;
	}
	return (i);
}
