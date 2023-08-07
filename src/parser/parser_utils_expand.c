/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:27:29 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/07 02:56:46 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// pseudocode

// look for expand ($)
// - function to iterate through strings
// of each node looking for $ (ISSUE! consider $$???)

int	ft_set_quote_state(char *str, int state, int i)
{
	if (str[i] == '\"' && !state)
		state = 1;
	if (str[i] == '\'' && !state)
		state = 2;
	return (state);
}

int	ft_confirm_expand(t_shell *shell)
{
	t_token	*aux;
	int		i;
	int		state;

	aux = shell->list;
	while (aux)
	{
		i = 0;
		state = 0;
		while (aux->str[i])
		{
			state = ft_set_quote_state(aux->str, state, i);
			if (aux->str[i] == '$' && state < 2 && aux->str[i + 1] != '\0'
				&& aux->str[i + 1] != ' ' && aux->str[i + 1] != '\"'
				&& aux->str[i + 1] != '\'' && aux->str[i + 1] != '$')
			{
				aux->type = EXPAND;
				break ;
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}
