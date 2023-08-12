/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_marks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:54:29 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/12 18:55:03 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_marks(t_shell *shell)
{
	ft_mark_redir_in_file(shell);
	ft_mark_redir_out_file(shell);
	ft_mark_append_file(shell);
	ft_mark_cmds(shell);
	ft_mark_args(shell);

	return (0);
}
