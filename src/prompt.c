/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:45 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/06 21:05:17 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//include modifications in add_history
//add_history cannot take "nothing", just "enter"
//recheck with Will Branner
int	ft_is_history(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	if (ft_strlen(tmp) != 0 || !tmp)
	{
		add_history(str);
		free(tmp);
		return (1);	
	}
	free(tmp);
	return (0);
}
