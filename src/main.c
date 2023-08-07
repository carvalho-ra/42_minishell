/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:37 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/06 23:37:52 by rcarvalh         ###   ########.fr       */
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
	shell->aux_lexer = 0;
	shell->temp_str = NULL;
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

static void	ft_aux(t_shell *shell)
{
	if (!shell->line)
	{
		write(2, "exit\n", 5);
		ft_builtin_exit(shell);
	}
	if (ft_is_history(shell->line))
	{
		shell->list = ft_lexer(shell);
		if (shell->list)
		{
			ft_validation(shell);
			//ft_print_list(shell);
			ft_expantion(shell);
			ft_print_list(shell);
			ft_join_from_lexer(shell);
			ft_parse_full_cmds(shell->list);
			ft_print_cmds(shell->list);
			ft_execution(shell);
			ft_free_token_list(shell);
			free(shell->line);
		}
	}
	else
		free(shell->line);
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
		shell->line = readline("OURSHELL> ");
		ft_aux(shell);
	}
	return (0);
}
