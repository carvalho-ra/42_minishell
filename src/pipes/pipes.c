/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:39:06 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/19 20:24:14 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


    // pid_t	pid;
	// int		child_exit_code;

    // pipe()
	// pid = fork();
	// child_exit_code = 0;
	// if (pid == -1)
	// {
	// 	printf("fork error\n");
	// 	return (-1);
	// }
	// else if (pid == 0)
	// {
	// 	ft_execution(shell);
	// 	exit(errno);
	// }
	// else
	// {
	// 	waitpid(pid, &child_exit_code, 0);
	// 	if (WIFEXITED(child_exit_code))
	// 	{
	// 		g_error_code = WEXITSTATUS(child_exit_code);
	// 		ft_free_ptrs(&cmd, NULL);
	// 	}
	// }
	// return (0);