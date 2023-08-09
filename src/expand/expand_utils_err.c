/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:24 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 18:00:55 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_aux_exp_err_flag(char *str, int i)
{
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '?')
	{
		i++;
		i++;
	}
	return (i);
}

char	*ft_aux_exp_err(char *str, char *final, int i)
{
	char	*ret;
	char	*sub;
	int		start;

	ret = (NULL);
	sub = NULL;
	start = 0;
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '?')
	{
		i++;
		i++;
		if (start != i && !final)
			ret = ft_itoa(g_error_code);
		else if (start != i && final)
		{
			sub = ft_itoa(g_error_code);
			ret = ft_strjoin(final, sub);
		}
	}
	ft_free_ptrs(&final, &sub);
	return (ret);
}
