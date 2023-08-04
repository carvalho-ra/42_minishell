/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:45 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/03 14:04:01 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//include modifications in add_history
//add_history cannot take "nothing", just "enter"
//recheck with Will Branner
void	ft_is_history(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	if (ft_strlen(tmp) != 0 || ft_strlen(str) != 0)
		add_history(str);
	free(tmp);
}
