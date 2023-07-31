/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:03:21 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/31 14:34:24 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO
//[ ] devia receber um t_token *current e a partir dele chegar na lista?

int ft_builtin_exit(t_shell *shell)
{
    printf("NA BUILTIN EXIT\n");
    free(shell->line);
    ft_free_token_list(shell);
	ft_free_env_list(shell);
	ft_free_env_strs(shell);
	free(shell);
    exit (0);
}

//free geral!

//régua cobra com parâmetro

//pegar o código de retorn (exit XXXX)

//quando sai com número pegar esse número e retornar

//quando sai com string exit code 2


