/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:29:17 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/27 05:47:38 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// funçao ft_count_args conta o número de argumentos, builtin ou não
// recebe o token de um comando e retorna o array de strings já mallocado;

char	**ft_count_args(t_token *token)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = token;
	while (aux && (aux->type >= 0 && aux->type <= EXPAND))
	{
		i++;
		aux = aux->next;
	}
	aux = token;
	aux->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(aux->cmd))
		return (NULL);
	return (aux->cmd);
}

// ft_fill_array recebe o token da lista e preenche
//o array de strings com as strings dos demais tokens

t_token *ft_fill_array(t_token *token)
{
	t_token	*current;
	t_token	*aux;
	int		i;
	current = token;
	if (current && (current->type >= 0 && current->type <= EXPAND))
		{
			i = 0;
			aux = current;//manter o ponteiro enquanto anda na lista
			aux->cmd = ft_count_args(current); //retorna o array de strings já mallocado
			while(current && (current->type >= 0 && current->type <= EXPAND)) //percorre com o auxiliar pra andar na lista
			{
				aux->cmd[i++] = ft_strdup(current->str); //copia da str para o array na posição i
				current = current->next;
			}
			aux->cmd[i] = NULL;//fecha este array cteste << teste 123om a ultima string NULL
		}
	return (current);
}

// ft_parse_full_cmds recebe a lista de tokens e separa em arrays de strings

void	ft_parse_full_cmds(t_token *list) //fazer como int pra retornar erro;
{
	t_token	*current; //vai apontar para a lista final (2a lista impressa)

	current = list; //aponta pro primeiro nó da lista para percorrê-la sem perder a lista
	while (current) //enquanto houver nodo, aqui vou dando dup nas str dos tokens e colocando no array
	{
		current = ft_fill_array(current); //retorna o ponteiro para o próximo nó
		if (!current)
			return ;
		else
			current = current->next;
	}
	return ;
}

// ft_print_cmds usada para verificar se os arrays estão completos

void	ft_print_cmds(t_token *list)
{
	t_token	*aux;
	int		i;

	aux = list;
	while (aux)
	{
		if (aux->cmd)
		{
			printf("\ntoken %i\n", aux->index);
			i = 0;
			while (aux->cmd[i])
			{
				printf ("%s\n", aux->cmd[i]);
				i++;
				if (aux->cmd[i] == NULL)
					printf("%s", "(null)\n"); 
			}
		}
		if (!aux->next)
			return ;
		else
			aux = aux->next;
	}
}

//ft_print_check usada para verificar se os tokens estavam sendo marcados direito

void	ft_print_check(t_shell *shell)
{
	t_token	*aux;

	aux = NULL;
	aux = shell->list;
	if (!aux)
		return ;
	while (aux)
	{
		if (aux->type)
		{
			printf("token index %i\n", aux->index);
			printf("token type %i\n", aux->type);
		}
		aux = aux->next;
	}
}
