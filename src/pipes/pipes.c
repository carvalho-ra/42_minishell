/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:39:06 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/20 12:27:49 by rcarvalh         ###   ########.fr       */
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
		}
		aux = aux->next;
	}
	return (0);
}
