/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_pid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:24 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 12:02:21 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_aux_exp_pid_flag(char *str, int i)
{
	if (str[i] && str[i] == '$' && str[i + 1] == '$')
	{
		i++;
		i++;
	}
	return (i);
}

char *ft_aux_exp_pid(char *str, char *final, int i)
{
	char *new;
	char	*ret;
	int	start;

	new = (NULL);
	start = 0;
	if (str[i] && str[i] == '$' && str[i + 1] == '$')
	{
		i++;
		i++;
		new = ft_itoa(getpid());
		if (start != i && !final)
			return (new);
		else if (start != i && final)
		{
			ret = ft_strjoin(final, new);
			free(new);
			new = NULL;
		}
	}
	return (ret);
}
