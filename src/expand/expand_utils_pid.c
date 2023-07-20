/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_pid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:24 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/19 21:44:19 by rcarvalh         ###   ########.fr       */
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
	int	start;

	new = (NULL);
	start = 0;
	if (str[i] && str[i] == '$' && str[i + 1] == '$')
	{
		i++;
		i++;
		if (start != i && !final)
			new = ft_itoa(getpid());
		else if (start != i && final)
			new = ft_strjoin(final, ft_itoa(getpid()));
	}
	return (new);
}
