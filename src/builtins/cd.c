/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:11:35 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/03 13:08:13 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
[X] deve ser feito com a nossa própria env
[X] não está trocando de pasta
[X] deve funcionar com o caminho relativo ../ ou ./
[X] deve funcionar com o caminho absoluto /home/minishell/src
[X] deve funcionar com "~"
[X] deve funcionar com "-"
*/

//function that substitutes existing OLDPWD for the current directory
int	ft_substitute_oldpwd(t_shell *shell, char *current_pwd)
{
	char	*temp;
	t_env	*aux;

	temp = ft_strdup("OLDPWD");
	aux = shell->env;
	while (aux)
	{
		if (ft_strncmp(temp, aux->str, 7) == 0)
		{
			free(aux->str);
			aux->str = ft_strjoin(temp, current_pwd);
			ft_free_ptrs(temp, current_pwd);
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}

// função que troca o OLDPWD pelo diretório em que estou
int	ft_change_oldpwd(t_shell *shell)
{
	char	*temp;
	char	*oldpwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	temp = ft_strdup("OLDPWD=");
	oldpwd = ft_search_env(temp, shell);
	if (!oldpwd)
	{
		ft_add_env(shell, ft_strjoin("OLDPWD=", current_pwd));
		ft_free_ptrs(oldpwd, current_pwd);
		return (0);
	}
	else
		ft_substitute_oldpwd(shell, current_pwd);
	return (1);
}

//function that changes directory to home
int	ft_goto_home(t_token *current)
{
	char	*temp;
	char	*path;

	ft_change_oldpwd(current->shell);
	temp = ft_strdup("HOME");
	path = ft_search_env(temp, current->shell);
	chdir(path);
	ft_free_ptrs(path, NULL);
	return (0);
}

//function that changes directory to last seen
int	ft_goto_prev_pwd(t_token *current)
{
	char	*temp;
	char	*oldpwd;

	temp = ft_strdup("OLDPWD");
	oldpwd = ft_search_env(temp, current->shell);
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD não definida\n", 2);
		ft_free_ptrs(oldpwd, NULL);
		return (0);
	}
	else
	{
		ft_change_oldpwd(current->shell);
		chdir(oldpwd);
		ft_free_ptrs(oldpwd, NULL);
		return (0);
	}
}

// Changes the current directory.
int	ft_builtin_cd(t_token *current)
{
	char	*path;

	printf("NA BUILTIN CD\n");
	path = NULL;
	if (!current->next || (current->next->str[0] == '~'
			&& current->next->str[1] == '\0'))
		return (ft_goto_home(current));
	else if (current->next->str[0] == '-' && current->next->str[1] == '\0')
		return (ft_goto_prev_pwd(current));
	else
	{
		path = current->next->str;
		if (chdir(path) == -1)
		{
			printf("minishell: cd: %s: ", path);
			printf("Arquivo ou diretório não encontrado\n");
			return (0);
		}
		ft_change_oldpwd(current->shell);
		chdir(path);
	}
	return (0);
}
