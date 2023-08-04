/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:52:17 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/03 12:10:57 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Gets current working directory and prints it to stdout.
int	ft_builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (0);
}
