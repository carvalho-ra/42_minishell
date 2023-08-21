/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 03:09:05 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/21 01:39:35 by rcarvalh         ###   ########.fr       */
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

void	ft_print_error_msg(char *str, char *msg, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_error_code = error_code;
}

void	ft_signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	ft_is_dir(char *path)
{
	DIR	*dir;

	if (!path)
		return (-1);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

//verifica se existe e se é executável
int	ft_is_executable(char *str)
{
	if (!str)
		return (-1);
	if (access(str, F_OK) != -1)
	{
		if (ft_is_dir(str) == 0 && access(str, X_OK) == 0)
			return (2);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			if (access(str, X_OK) == -1)
				ft_putstr_fd(": permissão negada\n", 2);
			else
				ft_putstr_fd(" é um diretório\n", 2);
			g_error_code = 126;
			return (-1);
		}
	}
	return (1);
}
