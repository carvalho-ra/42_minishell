/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/31 19:24:01 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO TRATAR ASPAS
//TODO 1 OK! remover aspas
//TODO 2 OK! (exceto se for aspas dentro de aspas)
//TODO 3 percorrer string; se só tiver uma aspa externa, imprimir nova linha até fecharem aspas
//TODO 4 expandir variáveis de ambiente

//TODO:
/*
[X] está dando erro de malloc - OK linha 66 (coloquei + 1 no malloc para o NULL - funcionou)
[X] echo $NOUSER - quando passa algo que não está na env (sozinho, com ou sem aspas
[ ] ela está trabalhando sempre com o primeiro nó. devia receber um t_token *current_node
*/

// Prints the arguments to stdout, separated by a space.
int	ft_builtin_echo(t_token *current)
{
	//t_token	*aux;
	char	**strings;
	int		slash_n; //* Flag para saber se usaram -n
	int		i;

	printf("NA BUILTIN ECHO\n");
	i = 1;
	slash_n = FALSE;
	strings = current->cmd;
	if (current->cmd && current->cmd[i][0] == '-' && current->cmd[i][1] == 'n') //* Aqui verifico se usaram -n
	{
		slash_n = TRUE; //* Se sim, levanto essa flag para no final do programa não pular linha
		i++; //* E vou para o próximo elemento do comando
	}
	while (strings[i])
	{
		strings[i] = quotes_treatment(strings[i]); //* Faço o tratamento das aspas
		ft_putstr_fd(strings[i], 1); //* Imprimo a string já tratada
		//free(strings[i]);
		if (strings[i + 1]) //* Se não for o último elemento, separo com um espaço
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (slash_n == FALSE) //* Se a flag do -n não tiver sido erguida lá em cima, pulo a linha
		ft_putstr_fd("\n", 1);
	return (TRUE); //* Devolvo 1 porque a função que chama essa função pergunta se é builtin, e é
}

char	*quotes_treatment(char *string)
{
	char	*tmp;

	tmp = NULL;
	if (string[0] == '\'') //* Se encontrar aspas
	{
		tmp = ft_strtrim(string, "\'");
		ft_free_ptrs(string, NULL);
		string = ft_strdup(tmp);
		ft_free_ptrs(tmp, NULL);
	}
	return (string);
}
