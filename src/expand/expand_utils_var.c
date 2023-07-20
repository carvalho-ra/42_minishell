/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:46 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 01:58:52 by rcarvalh         ###   ########.fr       */
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
	int	start;

	start = 0;
	new = (NULL);
	if (str[i] && str[i] == '$' && str[i + 1])
	{
		i++;
		start = i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (start != i && ft_search_env(ft_substr(str, start, i - start), shell) && !final)
			new = ft_search_env(ft_substr(str, start, i - start), shell);
		else if (start != i && ft_search_env(ft_substr(str, start, i - start), shell) && final)
			new = ft_strjoin(final, ft_search_env(ft_substr(str, start, i - start), shell));
	}
	return (new);
}