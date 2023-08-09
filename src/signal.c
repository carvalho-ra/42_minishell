/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:52 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 22:37:50 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handler(int signal)
{
	write (2, "\n", 1);
	if (signal == SIGINT)
	{
		rl_on_new_line ();
		rl_replace_line ("", 0);
		rl_redisplay ();
		g_error_code = 130;
	}
}

//apagar historico no processo filho!!!
//chamar função especifica da readline
