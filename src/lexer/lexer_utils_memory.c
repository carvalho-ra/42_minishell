/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:31:49 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/03 17:21:11 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that frees list of tokens
void	ft_free_token_list(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->list;
	while (current)
	{
		next = current->next;
		free(current->str);
		if (current->cmd)
			ft_free_arr_strs(current->cmd);
		free(current->cmd);
		free(current);
		current = next;
	}
	shell->list = NULL;
}
