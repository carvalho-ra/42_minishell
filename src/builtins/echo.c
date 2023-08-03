/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/03 13:15:21 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO TRATAR ASPAS
//TODO 1 OK! remover aspas
//TODO 2 OK! (exceto se for aspas dentro de aspas)
//TODO 3 percorrer string; se só tiver uma aspa externa,
//imprimir nova linha até fecharem aspas
//TODO 4 expandir variáveis de ambiente

/*
[X] está dando erro de malloc - OK
//linha 66 (coloquei + 1 no malloc para o NULL - funcionou)
[X] echo $NOUSER - quando passa algo que não está na env
//(sozinho, com ou sem aspas)
[X] ela está trabalhando sempre com o primeiro nó.
//Devia receber um t_token *current_node
*/

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
		if (strings[i])
			strings[i] = quotes_treatment(current->cmd[i]);
		ft_putstr_fd(strings[i], 1);
		if (strings[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (slash_n == FALSE)
		ft_putstr_fd("\n", 1);
	return (0);
}

char	*quotes_treatment(char *string)
{
	char	*tmp;

	tmp = NULL;
	if (string[0] == '\'')
	{
		tmp = ft_strtrim(string, "\'");
		ft_free_ptrs(string, NULL);
		string = ft_strdup(tmp);
		ft_free_ptrs(tmp, NULL);
	}
	return (string);
}
