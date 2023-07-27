/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:21 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/26 17:37:50 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_confirm_append(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->str[0] == '>' && aux->next && aux->next->str[0] == '>'
			&& aux->next->next && aux->next->next->str[0] != '>'
			&& aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->type = ERR;
			aux->next->type = APPEND;
			aux = aux->next;
			printf("\t\ttoken %i is append (>>)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_confirm_heredoc(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->str[0] == '<' && aux->next && aux->next->str[0] == '<'
			&& aux->next->next && aux->next->next->str[0] != '<'
			&& aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->type = ERR;
			aux->next->type = HEREDOC;
			aux = aux->next;
			printf("\t\ttoken %i is heredoc (<<)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

// o que vem do lado de um redirect é o nome do arquivo

int	ft_confirm_redir_out(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->str[0] == '>' && aux->next && aux->next->str[0] != '>'
			&& aux->type != APPEND && aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->type = REDIRECT_OUT;
			printf("\t\ttoken %i is redirect output (>)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_confirm_redir_in(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->str[0] == '<' && aux->next && aux->next->str[0] != '<'
			&& aux->type != HEREDOC && aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->type = REDIRECT_IN;
			printf("\t\ttoken %i is redirect input (<)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}
