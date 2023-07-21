/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:27:29 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 19:27:53 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// pseudocode

// look for expand ($)
// - function to iterate through strings
// of each node looking for $ (ISSUE! consider $$???)

int	ft_confirm_expand(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	while (aux)
	{
		i = 0;
		while (aux->str[i])
		{
			i = (ft_single_quote(aux->str, i));
			if (aux->str[i] == '$' && aux->str[i + 1])
			{
				aux->error_code = 0;
				aux->type = EXPAND;
				printf("token %i is expand\n", aux->index);
				break ;
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}
