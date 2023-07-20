/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:37 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/19 21:20:38 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_shell *ft_shell_init(t_shell *shell, char **envp)
{
	shell = NULL;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->expanded = NULL;
	shell->line = NULL;
	// shell->list = malloc(sizeof(t_token));
	// if (!shell->list)
	// 	return (NULL);
	shell->list = NULL;
	// shell->new_env = malloc(sizeof(t_token));
	// if (!shell->new_env)
	// 	return (NULL);
	shell->new_env = NULL;
	ft_copy_env(shell, envp);
	return (shell);
}

int main(int argc, char **argv, char **envp)
{
	t_shell *shell;

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
        shell->line = readline("minishell> "); // Prompt 
		// Ctrl+D (EOF)
		if (!shell->line) 
		{
			write(2, "exit\n", 5);
			break ;
		}
		// cmd exit
		if (ft_strcmp(shell->line, "exit") == 0)
		{
			//free user input
			free(shell->line);
			break ;
		}
		if (ft_strcmp(shell->line, "env") == 0)
		{
			//print env on call
			ft_builtin_env(shell);
			continue ;
		}
        // include readline/history.h
		ft_is_history(shell->line);
		shell->list = ft_lexer(shell);
		if (shell->list)
		{
			ft_print_list(shell);
			printf("\n");
			ft_err_pipe(shell);
			ft_err_redir_in(shell);
			ft_err_redir_out(shell);
			ft_confirm_pipe(shell);
			ft_confirm_append(shell);
			ft_confirm_heredoc(shell);
			ft_confirm_redir_in(shell);
			ft_confirm_redir_out(shell);
			
			// ft_confirm_redir(list);  -->got substituted by others
			ft_confirm_expand(shell);
			ft_is_builtin(shell);

			ft_vars_to_expand(shell);
			ft_free_token_list(shell);
		}
	}
	ft_free_token_list(shell);
	ft_free_env_list(shell);
	free(shell);
    return (0);
}
