/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:19:26 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/05 04:54:07 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//ASPAS DUPLAS removidas já no final do lexer
void	ft_expand_args(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (aux->type == EXPAND)
			aux->str = ft_expand_core(aux->str, shell);
		aux = aux->next;
	}
	ft_remove_quotes(shell);
}

char	*ft_expand_core(char *str, t_shell *shell)
{
	char	*final;
	int		i;

	i = 0;
	final = NULL;
	while (str[i])
	{
		if (i != ft_aux_exp_word_flag(str, i))
			final = ft_aux_exp_word(str, final, i);
		i = ft_aux_exp_word_flag(str, i);
		if (i != ft_aux_exp_pid_flag(str, i))
			final = ft_aux_exp_pid(str, final, i);
		i = ft_aux_exp_pid_flag(str, i);
		if (i != ft_aux_exp_var_flag(str, i))
			final = ft_aux_exp_var(str, final, i, shell);
		i = ft_aux_exp_var_flag(str, i);
	}
	ft_free_ptrs(str, NULL);
	return (final);
}

void	ft_free_ptrs(char *str, char *str2)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
}

void	ft_remove_quotes(t_shell *shell)
{
	t_token	*aux;
	char	*tmp;

	aux = shell->list;
	tmp = NULL;
	while (aux)
	{
		if (aux->str[0] == '\'')
		{
			tmp = ft_strtrim(aux->str, "\'");
			ft_free_ptrs(aux->str, NULL);
			aux->str = ft_strdup(tmp);
			ft_free_ptrs(tmp, NULL);
			if (aux->next)
				aux = aux->next;
		}
		if (aux->str[0] == '\"')
		{
			tmp = ft_strtrim(aux->str, "\"");
			ft_free_ptrs(aux->str, NULL);
			aux->str = ft_strdup(tmp);
			ft_free_ptrs(tmp, NULL);
			if (aux->next)
				aux = aux->next;
		}
		aux = aux->next;
	}
}
