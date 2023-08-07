/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/05 19:46:40 by rcarvalh         ###   ########.fr       */
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
	return (0);
}

// char	*quotes_treatment(char *string)
// {
// 	int		i;
// 	int		j;
// 	int		external; //* Flag para saber se estou 
//dentro das aspas externas, e que tipo são
// 	char	treated[ft_strlen(string)]; //* String que vai 
//substituir o input do usuário tirando aspas externas
// 	i = 0;
// 	j = 0;

// 	external = FALSE;
// 	while (string[i])
// 	{
// 		if (string[i] == '\'' || string[i] == '\"') //* Se encontrar aspas
// 		{
// 			if (string[i] == '\'' && external == FALSE)
// 				external = 1; //* Se for aspas simples, flag 1
// 			else if (string[i] == '\"' && external == FALSE)
// 				external = 2; //* Se for aspas duplas, flag 2
// 		}
// 		if (string[i] == '\'' && external == 1) //* Ignora as aspas externas
// 			i++;
// 		else if (string[i] == '\"' && external == 2)
// 			i++;
// 		else
// 		{
// 			treated[j] = string[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	treated[j] = '\0';
// 	ft_free_ptrs(string, NULL);
// 	string = ft_strdup(treated);
// 	return (string);
// }
