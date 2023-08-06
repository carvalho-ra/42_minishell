/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:43 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/06 11:24:06 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_aux_lexer(char *str, int i)
{
	while (str[i] && !(ft_is_blank(str[i])))
	{
		if (str[i] == 34)
			return (ft_double_quote(str, i));
		else if (str[i] == 39)
			return (ft_single_quote(str, i));
		else if (ft_is_pipe_redir(str[i]))
			return (i + 1);
		else
		{
			while (str[i] && !(ft_is_pipe_redir(str[i]))
				&& (str[i] != 34) && (str[i] != 39))
			{
				if (ft_is_blank(str[i]))
					break ;
				i++;
			}
			return (i);
		}
	}
	return (i);
}

t_token	*ft_lexer(t_shell *shell)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	id;

	i = 0;
	start = 0;
	id = 2;
	if (!shell->line)
		return (NULL);
	while (shell->line[i])
	{
		while (shell->line[i] && ft_is_blank(shell->line[i]))
			i++;
		start = i;
		i = ft_aux_lexer(shell->line, i);
		if (start != i)
			ft_add_token(shell, ft_substr(shell->line, start, i - start), id);
	}
	return (shell->list);
}
