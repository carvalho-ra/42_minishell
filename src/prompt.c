/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:45 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/07 01:28:00 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//include modifications in add_history
int	ft_is_history(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	if (ft_strlen(tmp) != 0)
	{
		add_history(str);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
