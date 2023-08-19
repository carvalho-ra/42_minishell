/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:37 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/19 17:00:05 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_error_code;

static	t_shell	*ft_shell_init(t_shell *shell, char **envp)
{
	shell = NULL;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->line = NULL;
	shell->list = NULL;
	shell->env_strs = NULL;
	shell->env = NULL;
	shell->pipe[0] = STDIN_FILENO;
	shell->pipe[1] = STDOUT_FILENO;
	shell->backup[0] = STDIN_FILENO;
	shell->backup[1] = STDOUT_FILENO;
	shell->aux_lexer = 0;
	shell->temp_str = NULL;
	ft_copy_env(shell, envp);
	return (shell);
}

void	ft_shell(t_shell *shell)
{
	if (!shell->line)
	{
		write(2, "exit\n", 5);
		ft_free_exit(shell);
	}
	if (ft_is_history(shell->line))
	{
		shell->list = ft_lexer(shell);
		if (shell->list)
		{
			if (!ft_parser(shell))
			{
				ft_execution(shell);
				ft_free_token_list(shell);
				free(shell->line);
			}
		}
	}
	else
	{
		rl_clear_history();
		free(shell->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = NULL;
	shell = ft_shell_init(shell, envp);
	(void)argv;
	(void)argc;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_handler);
	while (1)
	{
		if (g_error_code != 0)
			shell->line = readline("🤬 miniSHELL$ ");
		else
			shell->line = readline("😎 miniSHELL$ ");
		ft_shell(shell);
	}
	return (0);
}
