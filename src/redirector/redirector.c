/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:28:38 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/22 19:03:07 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Goes through the token list looking for redirectors.
// If it finds any, calls the respective function to load the input/output.
// Returns 0 if everything went well, -1 if there was an error.
int	ft_redirector(struct s_token *token)
{
	int		ret;
	t_token	*ref;

	ref = token;
	while (ref && (ref->type != CMD))
		ref = ref->next;
	if (!ref)
		ref = token;
	ret = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == HEREDOC)
			ret = ft_load_heredoc(token, ft_get_name(token));
		if (token->type == REDIRECT_IN)
			ret = ft_load_input(ref, ft_get_name(token));
		if (token->type == REDIRECT_OUT || token->type == APPEND)
			ret = ft_load_output(ref, ft_get_name(token), token->type);
		if (ret < 0)
			break ;
		token = token->next;
	}
	return (ret);
}

//function that returns the name of the file
//that is being redirected
char	*ft_get_name(t_token *token)
{
	while (token)
	{
		if (token->type == FILE_NAME || token->type == KEYWORD)
			return (token->str);
		token = token->next;
	}
	return (NULL);
}

// Checks every token that has a file descriptor, opens the input file
// to check if they're valid and readable. If not, it returns an error.
int	ft_load_input(struct s_token *token, char *filename)
{
	if (access(filename, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd (" : Arquivo ou diretório inexistente\n", 2);
		g_error_code = 1;
		return (-1);
	}
	if (access(filename, R_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : Permissão negada\n", 2);
		g_error_code = 1;
		return (-1);
	}
	g_error_code = 0;
	token->backup[0] = open(filename, O_RDONLY);
	return (0);
}

// Checks tokens that have an output file descriptor, and opens the output file,
// that is, checks if they exists. If not, creates the file.
int	ft_load_output(struct s_token *token, char *filename, int type)
{
	if (!access(filename, F_OK))
	{
		if (access(filename, W_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(" : Permissão negada\n", 2);
			g_error_code = 1;
			return (-1);
		}
	}
	if (type == REDIRECT_OUT)
		token->backup[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		token->backup[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->backup[1] < 0)
	{
		ft_putstr_fd("minishell: erro ao criar arquivo\n", 2);
		g_error_code = 1;
		return (-1);
	}
	g_error_code = 0;
	return (0);
}
