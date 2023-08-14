/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mark_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:54:18 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/14 10:38:24 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_mark_redir_in_file(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == REDIRECT_IN)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = FILE_NAME;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_mark_redir_out_file(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == REDIRECT_OUT)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = FILE_NAME;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_mark_append_file(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == APPEND)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = FILE_NAME;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_mark_heredoc_keyword(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == HEREDOC)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = KEYWORD;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}
