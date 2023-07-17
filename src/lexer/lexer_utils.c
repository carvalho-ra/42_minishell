#include "../../inc/minishell.h"

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	ft_is_pipe_redir(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	ft_is_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int ft_is_redir_more(char c)
{
	if (c == '>')
		return (1);
	else
		return (0);
}

int ft_is_redir_less(char c)
{
	if (c == '<')
		return (1);
	else
		return (0);
}
