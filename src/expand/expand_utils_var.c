/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:46 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 11:21:24 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_aux_exp_var_flag(char *str, int i)
{
	if (str[i] && str[i] == '$' && str[i + 1])
	{
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	return (i);
}

char *ft_aux_exp_var(char *str, char *final, int i, t_shell *shell)
{
	char	*new;
	char	*tmp;
	int	start;

	start = 0;
	tmp = (NULL);
	new = (NULL);
	if (str[i] && str[i] == '$' && str[i + 1])
	{
		i++;
		start = i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		tmp = ft_search_env(ft_substr(str, start, i - start), shell);
		if (start != i && tmp && !final)
			new = tmp;
		else if (start != i && tmp && final)
		{
			new = ft_strjoin(final, tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	return (new);
}