/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 07:56:38 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/17 13:55:41 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// This function is called when a heredoc is found in the token list.
// It loads the input from the heredoc into the token.
// It returns 0 if it succeeds, 1 if it fails.
int	ft_load_heredoc(t_token *token, char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	ft_reset_fds(token);
	return (fd[0]);
}
