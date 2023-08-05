/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:30:04 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/05 14:55:21 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_create_node(char *str, int index, t_shell *shell)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->index = index;
	new_node->type = 0;
	new_node->error_code = 0;
	new_node->str = str;
	new_node->cmd = NULL;
	new_node->shell = shell;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_token(t_shell *shell, char *str, int index)
{
	t_token	*aux;

	aux = NULL;
	aux = shell->list;
	if (aux == NULL)
		shell->list = ft_create_node(str, 1, shell);
	else
	{
		while (aux->next != NULL)
		{
			index++;
			aux = aux->next;
		}
		aux->next = ft_create_node(str, index, shell);
	}
}

void	ft_print_list(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		printf("\t\ttoken %i =  %s\n", aux->index, aux->str);
		aux = aux->next;
	}
}
