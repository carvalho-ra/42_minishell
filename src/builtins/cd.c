/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:11:35 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/31 19:32:12 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO
/*
[ ] deve ser feito com a nossa própria env
[ ] não está trocando de pasta
[ ] deve funcionar com o caminho relativo ../ ou ./
[ ] deve funcionar com o caminho absoluto /home/minishell/src
[ ] deve funcionar com "~"
*/

// Changes the current directory.
int	ft_builtin_cd(t_shell *shell)
{
	char	*path;

	path = shell->list->str;
	if (path == NULL || path[0] == '~')
		chdir(getenv("HOME"));
	else if (path[0] == '-')
		chdir(getenv("OLDPWD"));
	else
		chdir(path);
	return (1);
}

//*COMENTÁRIOS DO RODRIGO
// usar a prórpia export!!!!
//guardar o path em algum lugar
//guardar OLD path em algum lugar
//cd ..
//cd ../