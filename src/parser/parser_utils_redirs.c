/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:21 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/12 09:48:51 by cnascime         ###   ########.fr       */
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
			//printf("\t\ttoken %i is PIPE (|)\n", aux->index);
		}
		aux = aux->next;
	}
	return (0);
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
			aux->type = ERR;
			aux->next->type = HEREDOC;
			aux = aux->next;
			//printf("\t\ttoken %i is HEREDOC (<<)\n", aux->index);
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
			aux->type = REDIRECT_IN;
			//printf("\t\ttoken %i is REDIRECT_IN (<)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

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
			aux->type = REDIRECT_OUT;
			//printf("\t\ttoken %i is REDIRECT_OUT (>)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

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
			aux->type = ERR;
			aux->next->type = APPEND;
			aux = aux->next;
			//printf("\t\ttoken %i is APPEND (>>)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}
