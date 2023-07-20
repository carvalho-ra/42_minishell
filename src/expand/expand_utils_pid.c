/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_pid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:36:24 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 18:19:02 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_aux_exp_pid_flag(char *str, int i)
{
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '$')
	{
		i++;
		i++;
	}
	return (i);
}

char	*ft_aux_exp_pid(char *str, char *final, int i)
{
	char	*ret;
	char	*sub;
	int		start;

	ret = (NULL);
	sub = NULL;
	start = 0;
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '$')
	{
		i++;
		i++;
		if (start != i && !final)
			ret = ft_itoa(getpid());
		else if (start != i && final)
		{
			sub = ft_itoa(getpid());
			ret = ft_strjoin(final, sub);
			free(final);
			final = NULL;
			free(sub);
			sub = NULL;
		}
	}
	return (ret);
}
