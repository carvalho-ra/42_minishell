/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:30 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/26 10:39:58 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_create_node(char *str, int index)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->index = index;
	new_node->type = 0;
	new_node->error_code = 0;
	new_node->str = str;
	new_node->cmd = NULL;
	new_node->shell = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_token(t_shell *shell, char *str, int index)
{
	t_token	*aux;

	aux = NULL;
	aux = shell->list;
	if (aux == NULL)
		shell->list = ft_create_node(str, 1);
	else
	{
		while (aux->next != NULL)
		{
			index++;
			aux = aux->next;
		}
		aux->next = ft_create_node(str, index);
	}
}



void	ft_print_list(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		printf("\t\ttoken %i =  %s\n", aux->index, aux->str);
		aux = aux->next;
	}
}

void	ft_free_token_list(t_shell *shell)
{
	t_token	*current;
	t_token	*next;
	int		i;

	i = 0;
	current = shell->list;
	while (current)
	{
		next = current->next;
		free(current->str);
		if (current->cmd)
		{
			while (current->cmd[i])
			{
				free(current->cmd[i]);
				i++;
			}
		}
		free(current->cmd);
		free(current);
		current = next;
	}
	shell->list = NULL;
}

void	ft_free_env_list(t_shell *shell)
{
	t_env	*current;
	t_env	*next;

	current = shell->env;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	shell->env = NULL;
}

//AO FAZER NOVA STRUCT PARA MINISHELL
void	ft_free_shell(t_shell *shell)
{
	t_shell	*aux;

	aux = shell;
	free(aux->line);
	free(aux->env);
	free(aux->list);
	free(shell);
	shell = NULL;
}

//unitialized values: 
//

// ********************* TEST *********************
// char	**ft_add_envp(char **envp, char *node)
// {
// 	char	**envvariable;
// 	int		i;
// 	size_t	length;

// 	i = 0;
// 	if (!node)
// 		return (envp);
// 	// length = calcular tamanho da lista (libft)
// 	envvariable = malloc(sizeof(char *) * (length + 2));
// 	envvariable[length + 1] = NULL;
// 	if (!envvariable)
// 		return (envp);
// 	while (i < length)
// 	{
// 		envvariable[i] = ft_strdup(envp[i]);
// 		if (!envvariable[i])
// 		{
// 			//free envp
// 			//free envvariable;
// 		}
// 		i++;
// 	}
// 	envvariable[i] = ft_strdup(node);
// 	free(envp);
// 	return (envvariable);
// }
