/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:19:26 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/15 09:17:19 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//funtion thar calls expansion
void	ft_expansion(t_shell *shell)
{
	ft_confirm_expand(shell);
	ft_expand_args(shell);
}

//funtion that iterates through the list and calls expand
//each node previously marqued as expand
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

//core of expansion
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
		if (i != ft_aux_exp_err_flag(str, i))
			final = ft_aux_exp_err(str, final, i);
		i = ft_aux_exp_err_flag(str, i);
		if (i != ft_aux_exp_var_flag(str, i))
			final = ft_aux_exp_var(str, final, i, shell);
		i = ft_aux_exp_var_flag(str, i);
	}
	ft_free_ptrs(&str, NULL);
	return (final);
}

//function that remove quotes - last step of expansion
void	ft_remove_quotes(t_shell *shell)
{
	t_token	*aux;
	char	*tmp;
	char	*quotes;

	aux = shell->list;
	tmp = NULL;
	quotes = NULL;
	while (aux)
	{
		if (aux->str && (aux->str[0] == '\'' || aux->str[0] == '\"'))
		{
			quotes = ft_substr(aux->str, 0, 1);
			tmp = ft_strtrim(aux->str, quotes);
			ft_free_ptrs(&aux->str, NULL);
			aux->str = ft_strdup(tmp);
			ft_free_ptrs(&tmp, &quotes);
		}
		aux = aux->next;
	}
}

//function that joins strings marked as join previously in lexer
void	ft_join_from_lexer(t_shell *shell)
{
	t_token	*aux;
	char	*tmp;

	tmp = NULL;
	aux = shell->list;
	while (aux)
	{
		if (aux->join == 1)
		{
			if (aux && aux->next)
			{
				tmp = ft_strjoin(aux->str, aux->next->str);
				ft_free_ptrs(&aux->next->str, &aux->str);
				aux->next->str = ft_strdup(tmp);
				ft_free_ptrs(&tmp, NULL);
			}
		}
		aux = aux->next;
	}
}
