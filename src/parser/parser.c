/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:30 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/15 09:17:26 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_validation(t_shell *shell)
{
	if (ft_err_pipe(shell))
		return (1);
	else if (ft_err_redir_in(shell))
		return (1);
	else if (ft_err_redir_out(shell))
		return (1);
	return (0);
}

int	ft_parser(t_shell *shell)
{
	if (ft_validation(shell))
	{
		ft_free_token_list(shell);
		free(shell->line);
		return (1);
	}
	ft_confirm_pipe(shell);
	ft_confirm_append(shell);
	ft_confirm_heredoc(shell);
	ft_confirm_redir_in(shell);
	ft_confirm_redir_out(shell);
	//ft_print_list(shell);
	ft_expansion(shell);
	//ft_print_list(shell);
	ft_join_from_lexer(shell);
	ft_marks(shell);
	ft_parse_full_cmds(shell->list);
	//ft_print_cmds(shell->list);
	ft_print_check(shell);
	return (0);
}
