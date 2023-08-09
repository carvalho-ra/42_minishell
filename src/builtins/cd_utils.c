/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:35:48 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 16:04:14 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that substitutes existing OLDPWD for the current directory
int	ft_substitute_oldpwd(t_shell *shell, char *current_pwd)
{
	char	*temp;
	t_env	*aux;

	temp = ft_strdup("OLDPWD=");
	aux = shell->env;
	while (aux)
	{
		if (ft_strncmp(temp, aux->str, 7) == 0)
		{
			free(aux->str);
			aux->str = ft_strjoin(temp, current_pwd);
			ft_free_ptrs(&temp, NULL);
			return (0);
		}
		aux = aux->next;
	}
	return (0);
}

//function that changes OLDPWD for the current directory
int	ft_change_oldpwd(t_shell *shell, char *current_pwd)
{
	char	*temp;
	char	*oldpwd;

	temp = ft_strdup("OLDPWD");
	oldpwd = ft_search_env(temp, shell);
	temp = ft_strjoin("OLDPWD=", current_pwd);
	if (!oldpwd)
	{
		ft_add_env(shell, temp);
		ft_free_ptrs(&oldpwd, NULL);
		return (0);
	}
	else
	{
		ft_substitute_oldpwd(shell, current_pwd);
		ft_free_ptrs(&temp, &oldpwd);
		return (0);
	}
	return (1);
}

//function that changes directory to home
int	ft_goto_home(t_token *current, char *current_pwd)
{
	char	*temp;
	char	*path;

	ft_change_oldpwd(current->shell, current_pwd);
	temp = ft_strdup("HOME");
	path = ft_search_env(temp, current->shell);
	chdir(path);
	ft_free_ptrs(&path, &current_pwd);
	g_error_code = 0;
	return (0);
}

//function that changes directory to last seen
int	ft_goto_prev_pwd(t_token *current, char *current_pwd)
{
	char	*temp;
	char	*oldpwd;

	temp = ft_strdup("OLDPWD");
	oldpwd = ft_search_env(temp, current->shell);
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD não definida\n", 2);
		ft_free_ptrs(&oldpwd, &current_pwd);
		g_error_code = 0;
		return (0);
	}
	else
	{
		ft_change_oldpwd(current->shell, current_pwd);
		printf("%s\n", oldpwd);
		chdir(oldpwd);
		ft_free_ptrs(&oldpwd, &current_pwd);
		g_error_code = 0;
		return (0);
	}
}

//funtion that changes directory to the one above
int	ft_goto_above(t_token *current, char *current_pwd)
{
	char	*temp;
	int		i;

	i = 0;
	ft_change_oldpwd(current->shell, current_pwd);
	while (current_pwd[i])
		i++;
	while (current_pwd[i] != '/')
		i--;
	if (i == 0)
	{
		chdir("/home");
		ft_free_ptrs(&current_pwd, NULL);
		g_error_code = 0;
		return (0);
	}
	temp = ft_substr(current_pwd, 0, i);
	chdir(temp);
	ft_free_ptrs(&temp, &current_pwd);
	g_error_code = 0;
	return (0);
}
