/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:05 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 21:15:17 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_aux_exp_word_flag(char *str, int i)
{
	if ((str[i] && str[i] != '$') || (str[i] && str[i] == '$' && !str[i + 1]))
	{
		while ((str[i] && str[i] != '$')
			|| (str[i] && str[i] == '$' && !str[i + 1]))
			i++;
	}
	return (i);
}

char	*ft_aux_exp_word(char *str, char *final, int i)
{
	int		start;
	char	*new;
	char	*sub;

	start = 0;
	new = NULL;
	sub = NULL;
	if ((str[i] && str[i] != '$') || (str[i] && str[i] == '$' && !str[i + 1]))
	{
		start = i;
		while ((str[i] && str[i] != '$')
			|| (str[i] && str[i] == '$' && !str[i + 1]))
			i++;
		sub = ft_substr(str, start, i - start);
		if (start != i && !final)
			new = sub;
		else if (start != i && final)
			new = ft_strjoin(sub, final);
	}
	ft_free_ptrs(final, NULL);
	return (new);
}
