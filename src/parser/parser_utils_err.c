/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:17 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/26 17:38:26 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//when string initiates with <> next word is the name of a file to open/create
//is opened (created) and restart the prompt
//exit status 0

//when string initiates with > next word is the name of a file to open/create
//is opened (created) and restart the prompt
//exit status 0

//when string starts with >>> 
// bash: syntax error near unexpected token `>'
//exit error: 2

//when string initiates with >> (append) the file (named - next word)
//is opened (created) and restart the prompt

//when string initiates with >> (append) and the next char is | (a pipe) - ERROR
// bash: syntax error near unexpected token `|'
// error code: 2

// when string it ends with an append (>>) - ERROR
// bash: syntax error near unexpected token `newline'
// error code: 2

int	ft_err_pipe(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (!ft_strcmp("|", aux->str) && (!aux->next || aux == shell->list
				|| !ft_strcmp("|", aux->next->str)))
		{
			aux->error_code = 2;
			aux->type = ERR;
			while (aux->next && ft_is_pipe_redir(aux->next->str[0]))
			{
				aux->next->type = ERR;
				aux = aux->next;
			}
			printf("\t\ttoken %i, minishell: syntax error near unexpected token `|'\n", aux->index);
			break ;
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_err_redir_in(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if ((aux->str[0] == '<' && aux->next && aux->next->str[0] == '<'
				&& aux->next->next && ft_is_pipe_redir(aux->next->next->str[0]))
			|| (aux->str[0] == '<' && !aux->next))
		{
			aux->error_code = 1;
			aux->type = ERR;
			while (aux->next && ft_is_pipe_redir(aux->next->str[0]))
			{
				aux->next->type = ERR;
				aux = aux->next;
			}
			printf("\t\ttoken %i, minishell: syntax error near unexpected token `<'\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_err_redir_out(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if ((aux->str[0] == '>' && aux->next && aux->next->str[0] == '>'
				&& aux->next->next && ft_is_pipe_redir(aux->next->next->str[0]))
			|| (aux->str[0] == '>' && !aux->next))
		{
			aux->error_code = 1;
			aux->type = ERR;
			while (aux->next && ft_is_pipe_redir(aux->next->str[0]))
			{
				aux->next->type = ERR;
				aux = aux->next;
			}
			printf("\t\ttoken %i, minishell: syntax error near unexpected token `>'\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}
