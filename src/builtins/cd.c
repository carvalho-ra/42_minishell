/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:11:35 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/07 11:18:33 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// function that hanges the current directory.
int	ft_builtin_cd(t_token *current)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!current->next || (current->next->str[0] == '~'
			&& current->next->str[1] == '\0'))
		return (ft_goto_home(current, path));
	else if (current->next->str[0] == '-' && current->next->str[1] == '\0')
		return (ft_goto_prev_pwd(current, path));
	else if (current->next->str[0] == '.' && current->next->str[1] == '.'
		&& current->next->str[2] == '\0')
		return (ft_goto_above(current, path));
	else
	{
		if (chdir(current->next->str) == -1)
		{
			printf("minishell: cd: %s: ", current->next->str);
			printf("Arquivo ou diretório inexistente\n");
			ft_free_ptrs(&path, NULL);
			return (0);
		}
		ft_change_oldpwd(current->shell, path);
		chdir(current->next->str);
		ft_free_ptrs(&path, NULL);
	}
	return (0);
}
