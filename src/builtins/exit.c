/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:03:21 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/20 14:33:12 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that frees the t_env list, the t_token list and the line
//and exits the program
//returns 0 if it works, 1 if it doesn't
int	ft_free_exit(t_shell *shell)
{
	free(shell->line);
	ft_free_token_list(shell);
	ft_free_env_list(shell);
	ft_free_env_strs(shell);
	free(shell);
	rl_clear_history();
	g_error_code = 0;
	exit (0);
}

//function that frees the t_env list, the t_token list and the line
//returns 0 if it works, 1 if it doesn't
int	ft_free_no_exit(t_shell *shell)
{
	free(shell->line);
	ft_free_token_list(shell);
	ft_free_env_list(shell);
	ft_free_env_strs(shell);
	free(shell);
	rl_clear_history();
	return (0);
}

//free geral!
//régua cobra com parâmetro
//pegar o código de retorn (exit XXXX)
//quando sai com número pegar esse número e retornar
//quando sai com string exit code 2
int	ft_builtin_exit(t_token *current)
{
	int	i;

	i = 0;
	if (current->cmd[1])
	{
		if (ft_isdigit(current->cmd[1][0]) || current->cmd[1][0] == '-')
		{
			i = ft_atoi(current->cmd[1]);
			if (i < 0)
				i = 256 + i;
			ft_free_no_exit(current->shell);
			exit (i);
		}
		else
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(current->cmd[1], 1);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_free_no_exit(current->shell);
			exit (2);
		}
	}
	else
		ft_free_exit(current->shell);
	return (0);
}
