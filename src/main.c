/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:37 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/05 05:01:30 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_copy_env(shell, envp);
	return (shell);
}

static	void	ft_validation(t_shell *shell)
{
	ft_err_pipe(shell);
	ft_err_redir_in(shell);
	ft_err_redir_out(shell);
	ft_confirm_pipe(shell);
	ft_confirm_append(shell);
	ft_confirm_heredoc(shell);
	ft_confirm_redir_in(shell);
	ft_confirm_redir_out(shell);
}

static void	ft_expantion(t_shell *shell)
{
	ft_confirm_expand(shell);
	ft_expand_args(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = NULL;
	shell = ft_shell_init(shell, envp);
	(void)argv;
	(void)argc;
    //ignore SIGQUIT Ctrl+'\'
	signal(SIGQUIT, SIG_IGN);
    //treat SIGINT Ctrl+C
	signal(SIGINT, &ft_handler);
	while (1)
	{
		shell->line = readline("OURSHELL> ");
		// Ctrl+D (EOF)
		if (!shell->line)
		{
			write(2, "exit\n", 5);
			ft_builtin_exit(shell);
		}
		ft_is_history(shell->line);
		shell->list = ft_lexer(shell);
		if (shell->list)
		{
			ft_validation(shell);
			//ft_print_list(shell);
			ft_expantion(shell);
			//ft_print_list(shell);
			ft_parse_full_cmds(shell->list);
			//ft_print_cmds(shell->list);
			ft_execution(shell);
			ft_free_token_list(shell);
			free(shell->line);
		}
	}
	return (0);
}
