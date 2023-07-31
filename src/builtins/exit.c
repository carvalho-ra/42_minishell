/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:57:45 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/29 00:24:43 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_builtin_exit(t_shell *shell, t_env *env)
{
	(void)shell; //!temporary
	(void)env; //!temporary
	//free split (env->str);
	//free node (commands);
	//free (env);
	//exit (status);
	return ;//!temporary
}

// Comentários do Rodrigo:
//free geral!
//régua cobra com parâmetro
//pegar o código de retorn (exit XXXX)
//quando sai com número pegar esse número e retornar
//quando sai com string exit code 2
