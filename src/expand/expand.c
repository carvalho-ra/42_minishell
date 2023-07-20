/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:19:26 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 18:12:47 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// pseudocode

// look for expand ($)
// - function to iterate through strings
// of each node looking for $ (ISSUE! consider $$???)

int	ft_confirm_expand(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	while (aux)
	{
		i = 0;
		while (aux->str[i])
		{
			i = (ft_single_quote(aux->str, i));
			if (aux->str[i] == '$' && aux->str[i + 1])
			{
				aux->error_code = 0;
				aux->type = EXPAND;
				printf("token %i is expand\n", aux->index);
				break ;
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}

void	ft_expand_args(t_shell *shell)
{
	t_token	*aux;
	char	*prep_exp;

	aux = shell->list;
	while (aux)
	{
		if (aux->type == EXPAND)
		{
			prep_exp = ft_prep_expand(aux->str);
			free (aux->str);
			aux->str = NULL;
			aux->str = ft_expand_core(prep_exp, shell);
		}
		aux = aux->next;
	}
}

// apagar aspas duplas
// apagar aspas simples e nao faz mais nada
// cortar a variavel que vai expandir
// é só a varivel??

char	*ft_prep_expand(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	if (tmp[i] == 34)
		tmp = ft_strtrim(tmp, "\"");
	else
		tmp = ft_strdup(tmp);
	return (tmp);
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
	free(str);
	str = (NULL);
	return (final);
}
