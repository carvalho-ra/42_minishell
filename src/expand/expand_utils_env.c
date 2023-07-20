/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:39:46 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/20 18:21:40 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO need to export more than 1 variable at the same time? in the same line

// ler regras do export (man) 

// ler regras variaveis shell

//unset em variavel inexistente é igual ao comportamento normal, não dá erro

int	ft_copy_env(t_shell *shell, char **envp)
{
	int		i;

	shell->new_env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_add_env(shell, ft_strdup((const char *)envp[i]), 1);
		i++;
	}
	return (0);
}

// O CÓDIGO A SEGUIR ESTÁ CORRETO???

// int ft_copy_env(t_shell *shell, char **envp)
// {
// 	int		i;
// 	char *env_line;

// 	shell->new_env = NULL;
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		env_line = ft_strdup((const char *)envp[i]);
// 		ft_add_env(shell, env_line, 1);
// 		i++;
// 	}
// 	free(env_line);
// 	return (0);
// }

char	*ft_search_env(char *str, t_shell *shell)
{
	t_token	*aux;
	char	*ret;

	aux = shell->new_env;
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
	free (str);
	str = (NULL);
	return (ret);
}

//procurar com ft_strcmp(env);

//colocar em um loop para pagar string previa concatenar 
//com a parte do ENV, e continuar

// strdup do strlen + 1 pra pular o igual da variavel;

//retorna string expandida
