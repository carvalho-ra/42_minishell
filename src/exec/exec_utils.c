/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 03:09:05 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/07 11:27:03 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that transforms the t_env into a char **env
//to pass to execve
//returns 0 if it works, 1 if it doesn't
int	ft_env_to_str(t_shell *shell)
{
	t_env	*aux;
	int		i;

	i = 0;
	aux = shell->env;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	shell->env_strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->env_strs)
		return (1);
	i = 0;
	aux = shell->env;
	while (aux)
	{
		shell->env_strs[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
	shell->env_strs[i] = NULL;
	return (0);
}
