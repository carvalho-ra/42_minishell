/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/31 17:24:25 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO TRATAR ASPAS
//TODO 1 OK! remover aspas
//TODO 2 OK! (exceto se for aspas dentro de aspas)
//TODO 3 percorrer string; se só tiver uma aspa externa, imprimir nova linha até fecharem aspas
//TODO 4 expandir variáveis de ambiente

// Prints the arguments to stdout, separated by a space.
int	ft_builtin_echo(t_shell *shell)
{
	t_token	*aux;
	int		index;
	int		dash_n; //* Flag para saber se usaram -n
	char	*string;

	dash_n = FALSE;
	aux = shell->list->next;
	if (aux->str[0] == '-' && aux->str[1] == 'n') //* Aqui verifico se usaram -n
	{
		dash_n = TRUE; //* Se sim, levanto essa flag para no final do programa não pular linha
		aux = aux->next; //* E vou para o próximo elemento do comando
	}
	while (aux)
	{
		string = aux->str;
		index = 0;
		while (aux->str[index]) // Se tiver aspas, faz tratamento.
		{
			if (ft_isforbidden(aux->str[index], "\'\""))
			{
				string = quotes_treatment(aux->str);
				break ;
			}
			index++;
		}
		ft_putstr_fd(string, 1); //* Imprimo a string já tratada
		//free(string); // acusa double free
		if (aux->next) //* Se não for o último elemento, separo com um espaço
			ft_putstr_fd(" ", 1);
		aux = aux->next;
	}
	if (dash_n == FALSE) //* Se a flag do -n não tiver sido erguida lá em cima, pulo a linha
		ft_putstr_fd("\n", 1);
	return (TRUE); //* Devolvo 1 porque a função que chama essa função pergunta se é builtin, e é
}

char	*quotes_treatment(char *string)
{
	int		i;
	int		j;
	int		external; //* Flag para saber se estou dentro das aspas externas, e que tipo são
	char	*treated; //* String que vai substituir o input do usuário tirando aspas externas

	i = 0;
	j = 0;
	external = FALSE;
	treated = malloc(sizeof(char) * ft_strlen(string));
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"') //* Se encontrar aspas
		{
			if (string[i] == '\'' && external == FALSE)
				external = 1; //* Se for aspas simples, flag 1
			else if (string[i] == '\"' && external == FALSE)
				external = 2; //* Se for aspas duplas, flag 2
		}
		if (string[i] == '\'' && external == 1) //* Ignora as aspas externas
			i++;
		else if (string[i] == '\"' && external == 2)
			i++;
		else
		{
			treated[j] = string[i];
			i++;
			j++;
		}
	}
	treated[j] = '\0';
	//printf("treated: %s\n", treated);
	//printf("string: %s\n", string);
	//free(string);
	return (treated);
	//free(treated); // acusa double free, mas tenho medo de vazar depois
}
