/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 07:56:38 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/22 18:23:41 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// This function is called when a heredoc is found in the token list.
// It loads the input from the heredoc into the token.
int	ft_load_heredoc(t_token *token, char *delimiter)
{
	char	*line;
	int		fd[2];

	//TODO Verificar sinais quando heredoc estiver aberto
	if (pipe(fd) == -1)
		return (-1);
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd[OUT]);
		free(line);
	}
	free(line);
	close(fd[OUT]);
	dup2(fd[IN], token->pipe[IN]);
	/*(void)token;
	dup2(fd[IN], STDIN_FILENO);*/
	return (0);
}

/*int	ft_load_heredoc(t_token *token, char *delimiter)
{
	int		fd;
	char	*line;

	// Truncate or append?
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	printf("\t\tfd = %d\n", fd);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	printf("\t\ttoken->pipe[0] = %d\t\ttoken->pipe[1] = %d\n", token->pipe[0], token->pipe[1]);
	dup2(fd, token->pipe[0]);
	printf("\t\ttoken->pipe[0] = %d\t\ttoken->pipe[1] = %d\n", token->pipe[0], token->pipe[1]);
	close(fd);
	printf("\t\ttoken->pipe[0] = %d\t\ttoken->pipe[1] = %d\n", token->pipe[0], token->pipe[1]);
	return (0);
}*/
