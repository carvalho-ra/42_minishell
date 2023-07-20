/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:25 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/19 21:21:26 by rcarvalh         ###   ########.fr       */
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
		if (aux->str[0] == '|')
			i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_count_redirs(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->str[0] == '>' || aux->str[0] == '<')
			i++;
		aux = aux->next;
	}
	return (i);
}
