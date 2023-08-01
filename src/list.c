/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:30 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/31 19:32:58 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_create_node(char *str, int index, t_shell *shell)
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
	new_node->shell = shell;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_token(t_shell *shell, char *str, int index)
{
	t_token	*aux;

	aux = NULL;
	aux = shell->list;
	if (aux == NULL)
		shell->list = ft_create_node(str, 1, shell);
	else
	{
		while (aux->next != NULL)
		{
			index++;
			aux = aux->next;
		}
		aux->next = ft_create_node(str, index, shell);
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

void ft_free_arr_strs(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
}

void	ft_free_token_list(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->list;
	while (current)
	{
		next = current->next;
		free(current->str);
		if (current->cmd)
			ft_free_arr_strs(current->cmd);
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

void	ft_free_env_strs(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env_strs)
		return ;
	while (shell->env_strs[i])
	{
		free(shell->env_strs[i]);
		i++;
	}
	free(shell->env_strs);
	shell->env_strs = NULL;
}

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
