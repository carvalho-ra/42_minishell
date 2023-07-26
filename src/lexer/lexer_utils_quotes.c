/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:36 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/24 23:56:51 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_single_quote(char *str, int i)
{
	if (str[i] == 39)
	{
		i++;
		while (str[i] && str[i] != 39)
			i++;
		return (i);
	}
	return (i);
}

int	ft_double_quote(char *str, int i)
{
	if (str[i] == 34)
	{
		i++;
		while (str[i] != '\0' && str[i] != 34)
			i++;
		return (i);
	}
	return (i);
}
