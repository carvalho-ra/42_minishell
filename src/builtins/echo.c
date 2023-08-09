/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/08 15:59:44 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prints the arguments to stdout, separated by a space.
int	ft_builtin_echo(t_token *current)
{
	char	**strings;
	int		i;
	int		slash_n;

	strings = current->cmd;
	slash_n = FALSE;
	i = 1;
	if (strings[i] && ft_strcmp(strings[i], "-n") == 0)
	{
		slash_n = TRUE;
		i++;
	}
	while (strings[i])
	{
		ft_putstr_fd(strings[i], 1);
		if (strings[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (slash_n == FALSE)
		ft_putstr_fd("\n", 1);
	g_error_code = 0;
	return (0);
}
