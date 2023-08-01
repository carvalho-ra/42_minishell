/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:43 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/31 15:46:57 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_aux_lexer(char *str, int i)
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
	ft_remove_double_quotes(shell);
	return (shell->list);
}

void	ft_remove_double_quotes(t_shell *shell)
{
	t_token	*aux;
	char	*tmp;

	aux = shell->list;
	tmp = NULL;
	while (aux)
	{
		if (aux->str[0] == 34)
		{
			tmp = ft_strtrim(aux->str, "\"");
			ft_free_ptrs(aux->str, NULL);
			aux->str = ft_strdup(tmp);
			ft_free_ptrs(tmp, NULL);
		}
		aux = aux->next;
	}
}