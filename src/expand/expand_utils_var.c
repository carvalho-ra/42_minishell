/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:46 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 22:30:13 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that flags variable to expand
int	ft_aux_exp_var_flag(char *str, int i)
{
	if (str[i] && str[i] == '$' && ((str[i + 1] && str[i + 1] != '$')
			&& (str[i + 1] && str[i + 1] != '?')))
	{
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	return (i);
}

// auxiliar function to expand variables
char	*ft_norm_aux_exp_var(char *tmp, char *final, int start, int i)
{
	char	*new;

	new = NULL;
	if (start != i && tmp && final)
	{
		new = ft_strjoin(final, tmp);
		ft_free_ptrs(&tmp, &final);
	}
	else if ((start != i && tmp && !final))
	{
		new = tmp;
		ft_free_ptrs(&final, NULL);
	}
	else if (start != i && !tmp && final)
		new = final;
	return (new);
}

//function that expands variable and joins with the rest
char	*ft_aux_exp_var(char *str, char *final, int i, t_shell *shell)
{
	char	*new;
	char	*tmp;
	int		start;

	start = 0;
	tmp = (NULL);
	new = (NULL);
	if (str[i] && str[i] == '$' && ((str[i + 1] && str[i + 1] != '$')
			&& (str[i + 1] && str[i + 1] != '?')))
	{
		i++;
		start = i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		tmp = ft_search_env(ft_substr(str, start, i - start), shell);
		new = ft_norm_aux_exp_var(tmp, final, start, i);
	}
	return (new);
}
