/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/22 12:49:47 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO TRATAR ASPAS
//TODO 1 OK! remover aspas
//TODO 2 OK! (exceto se for aspas dentro de aspas)
//TODO 3 percorrer string; se só tiver uma aspa externa, imprimir nova linha até a segunda
//TODO 4 expandir variáveis de ambiente

// Prints the arguments to stdout, separated by a space.
int	ft_builtin_echo(t_shell *shell)
{
	t_token	*aux;
	char	*string;
	int		slash_n;

	string = NULL;
	slash_n = FALSE;
	aux = shell->list->next;
	if (aux->data[0] == '-' && aux->data[1] == 'n')
	{
		slash_n = TRUE;
		aux = aux->next;
	}
	while (aux)
	{
		string = quotes_treatment(aux->data);
		ft_putstr_fd(string, 1);
		if (aux->next)
			ft_putstr_fd(" ", 1);
		aux = aux->next;
	}
	if (slash_n == FALSE)
		ft_putstr_fd("\n", 1);
	return (1);
}

char	*quotes_treatment(char *string)
{
	int		i;
	int		j;
	int		external;
	char	*treated;
	//TODO Buscar e classificar aspas externas
	i = 0;
	j = 0;
	external = FALSE;
	treated = malloc(sizeof(char) * ft_strlen(string));
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
		{
			if (string[i] == '\'' && external == FALSE)
				external = 1;
			else if (string[i] == '\"' && external == FALSE)
				external = 2;
		}
		if (string[i] == '\'' && external == 1)
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
