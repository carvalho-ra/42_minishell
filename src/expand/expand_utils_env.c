/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:39:46 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/02 19:59:16 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*ft_create_env_node(char *str)
{
	t_env	*new_env_node;

	new_env_node = malloc(sizeof(t_token));
	if (!(new_env_node))
		return (NULL);
	new_env_node->str = str;
	new_env_node->next = NULL;
	return (new_env_node);
}

void	ft_add_env(t_shell *shell, char *str)
{
	t_env	*aux;

	aux = shell->env;
	if (aux == NULL)
		shell->env = ft_create_env_node(ft_strdup(str));
	else
	{
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = ft_create_env_node(ft_strdup(str));
	}
	ft_free_ptrs(str, NULL);
}

// ler regras variaveis shell
//unset em variavel inexistente é igual ao comportamento normal, não dá erro

int	ft_copy_env(t_shell *shell, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_add_env(shell, ft_strdup((const char *)envp[i]));
		i++;
	}
	return (0);
}

//procurar com ft_strcmp(env);

//colocar em um loop para pagar string previa concatenar 
//com a parte do ENV, e continuar

// strdup do strlen + 1 pra pular o igual da variavel;

//retorna string expandida

char	*ft_search_env(char *str, t_shell *shell)
{
	t_env	*aux;
	char	*ret;

	aux = shell->env;
	ret = NULL;
	while (aux)
	{
		if (!ft_strncmp(str, aux->str, ft_strlen(str))
			&& aux->str[ft_strlen(str)] == '=')
		{
			ret = ft_substr(aux->str, (ft_strlen(str) + 1),
					ft_strlen(aux->str) - (ft_strlen(str) + 1));
			break ;
		}
		aux = aux->next;
	}
	ft_free_ptrs(str, NULL);
	return (ret);
}
