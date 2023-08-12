/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 07:56:38 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/12 08:38:26 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// This function is called when a heredoc is found in the token list.
// It loads the input from the heredoc into the token.
// It returns 0 if it succeeds, 1 if it fails.
int	ft_load_heredoc(struct s_token *token)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	while (ft_strcmp(token->next->str, token->str) != 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, token->next->str) == 0)
		{
			printf("\t\tFim do heredoc!\n");
			//free(line);
			break ;
		}
		ft_putendl_fd(line, fd); //Preciso disso ou não?
		free(line);
	}
	printf("\t\tSaiu do loop!\n");
	close(fd);
	//ft_reset_fds(token);
	return (0);
}
