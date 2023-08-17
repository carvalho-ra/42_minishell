/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:21 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/17 13:53:31 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//when string initiates with | (a pipe) - ERROR
// bash: syntax error near unexpected token `|'
// error code: 2

//when string ends with | (a pipe) - ERROR
// bash: syntax error near unexpected token `newline'
// error code: 2

// redirect + PIPE é erro? ver com mais pessoas!!!!

// O que vem do lado de um pipe é um comando.
// O que vem do lado de um redirect é o nome do arquivo.

int	ft_confirm_pipe(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (!ft_strcmp("|", aux->str) && aux->next
			&& ft_strcmp("|", aux->next->str) && aux->type != ERR)
		{
			aux->type = PIPE;
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_confirm_heredoc(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (aux->str[0] == '<' && aux->next && aux->next->str[0] == '<'
			&& aux->next->next && aux->next->next->str[0] != '<'
			&& aux->type != ERR)
		{
			aux->type = ERR;
			aux->next->type = HEREDOC;
			aux = aux->next;
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_confirm_redir_in(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (aux->str[0] == '<' && aux->next && aux->next->str[0] != '<'
			&& aux->type != HEREDOC && aux->type != ERR)
		{
			aux->type = REDIRECT_IN;
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_confirm_redir_out(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (aux->str[0] == '>' && aux->next && aux->next->str[0] != '>'
			&& aux->type != APPEND && aux->type != ERR)
		{
			aux->type = REDIRECT_OUT;
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_confirm_append(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (aux->str[0] == '>' && aux->next && aux->next->str[0] == '>'
			&& aux->next->next && aux->next->next->str[0] != '>'
			&& aux->type != ERR)
		{
			aux->type = ERR;
			aux->next->type = APPEND;
			aux = aux->next;
		}
		aux = aux->next;
	}
	return (0);
}
