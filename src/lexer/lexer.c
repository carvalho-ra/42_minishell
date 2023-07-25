/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:43 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/25 15:47:36 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_aux_lexer(char *str, int i)
{
	while (str[i] && !(ft_is_blank(str[i])))
	{
		i = ft_double_quote(str, i);
		if (str[i])
			i = ft_single_quote(str, i);
		if (str[i])
			i++;
		if (ft_is_pipe_redir(str[i - 1]) || ft_is_pipe_redir(str[i]))
			break ;
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
